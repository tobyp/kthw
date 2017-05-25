/* KTHW - Hardware Clone of Keep Talking and Nobody Explodes
Copyright (C) 2017 Toby P., Thomas H.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include "bomb.h"

enum bomb_state {
	BS_READING_FLAGS,
	/* entered after BS_READING_FLAGS and the start button is pressed */
	BS_WAITING,
	/* entered after BS_READING_FLAGS when the start button is not released */
	BS_INITIALIZING_MODULES,
	/* when all modules have MF_READY set, */
	BS_COUNTDOWN,
	/* from BS_COUNTDOWN, when time runs out or the strike limit is passed */
	BS_EXPLODED,
	/* from BS_COUNTDOWN, when all modules have MF_COMPLETE or MF_NEEDY */
	BS_DEFUSED,
};

static void bomb_reset(struct bomb * bomb) {
	for (struct module * m = bomb->modules; m != NULL; m = m->next) {
		if (m->reset) {
			m->reset(bomb, m);
		}
	}
}

void bomb_add_module(struct bomb * bomb, struct module * module) {
	module->next = bomb->modules;
	bomb->modules = module;
}

void strike(struct bomb * bomb, struct module * module) {
	printf("[bomb] strike %d from %s\n", ++bomb->strikes, module->name);
	bomb->buzzer_timer = STRIKE_BUZZER_TICKS;
	bomb->timer_decrement += 25;
	gpio_set(bomb->buzzer, 1);
}

void explode(struct bomb * bomb, char const* cause) {
	printf("[bomb] exploded: %s\n", cause);
	bomb->state = BS_EXPLODED;
	bomb->buzzer_timer = (bomb->flags & FL_MERCIFUL) ? PUNISH_BUZZER_TICKS : ~0ul;
	gpio_set(bomb->buzzer, 1);
	bomb_reset(bomb);
	return;
}

void defuse(struct bomb * bomb) {
	printf("[bomb] defused\n");
	bomb->state = BS_DEFUSED;
	bomb->buzzer_timer = 0;
	gpio_set(bomb->buzzer, 0);
	bomb_reset(bomb);
}

void tick(struct bomb * bomb) {
	//update buzzer timers
	if (bomb->buzzer_timer > 0 && bomb->buzzer_timer != ~0ul) {
		bomb->buzzer_timer--;
		if (bomb->buzzer_timer == 0) {
			gpio_set(bomb->buzzer, 0);
		}
	}

	if (bomb->buzzer2_timer > 0) {
		bomb->buzzer2_timer--;
		if (bomb->buzzer2_timer == 0) {
			gpio_set(bomb->buzzer2, 0);
		}
	}

	switch (bomb->state) {
		case BS_READING_FLAGS: {
			uint8_t fl0 = gpio_get(bomb->in_flags[0]);
			uint8_t fl1 = gpio_get(bomb->in_flags[1]);

			if (bomb->flags_read_progress) {
				bomb->flags = (bomb->flags << 1) | fl0;
				bomb->flags_time = (bomb->flags_time << 1) | fl1;
			}

			if (bomb->flags_read_progress == 0xff) {
				printf(" ,*  KTHW v1.2\n(_)  (c) 2017 Toby P., Thomas H.\n    THIS IS NOT A REAL BOMB, IT IS HARMLESS.\n");
				bomb->state = BS_INITIALIZING_MODULES;

				bomb->timer = ((bomb->flags_time >> 2) & 0x3f) * 15 * TICKS_PER_SEC * 100;
				bomb->strike_limit = bomb->flags_time & 0x03;

				uint32_t secs = bomb->timer / TICKS_PER_SEC / 100;
				uint32_t mins = secs / 60 % 100;
				secs %= 60;
				printf("[bomb] timer=%d:%d strikelimit=%d flags=%x\n", mins, secs, bomb->strike_limit, bomb->flags);
			}
			else {
				bomb->sr_flags[0]->value = bomb->sr_flags[1]->value = bomb->flags_read_progress + 1;
				bomb->flags_read_progress = (bomb->flags_read_progress << 1) | 1;
			}
		} break;
		case BS_INITIALIZING_MODULES: {
			uint32_t all_ready = 1;
			for (struct module * m = bomb->modules; m != NULL; m = m->next) {
				if (!(m->flags & MF_READY)) {
					if (m->prepare_tick) {
						m->prepare_tick(bomb, m);
					}
				}
				if (!(m->flags & MF_READY)) {
					all_ready = 0;
				}
			}

			if (all_ready) {
				bomb->state = BS_WAITING;
			}
		} break;
		case BS_WAITING:
			if (!gpio_get(bomb->start_in)) {
				bomb->state = BS_COUNTDOWN;
			}
			break;
		case BS_COUNTDOWN: {
			//countdown timer
			uint32_t old_secs = bomb->timer / TICKS_PER_SEC / 100 % 60;
			uint32_t decrement = bomb->timer_decrement + 100;
			bomb->timer = (bomb->timer <= decrement) ? 0 : bomb->timer - decrement;
			if (bomb->timer == 0) {
				explode(bomb, "timeout");
				return;
			}
			uint32_t secs = bomb->timer / TICKS_PER_SEC / 100;
			uint32_t mins = secs / 60 % 100;
			secs = secs % 60;
			bomb->sr_timer[0]->value = sevenseg_digits[secs / 1 % 10];
			bomb->sr_timer[1]->value = sevenseg_digits[secs / 10 % 10];
			bomb->sr_timer[2]->value = SEVENSEG_WITH_DOT(sevenseg_digits[mins / 1 % 10]);
			bomb->sr_timer[3]->value = sevenseg_digits[mins / 10 % 10];

			//strikes
			if (bomb->strikes > bomb->strike_limit) {
				explode(bomb, "strikeout");
				return;
			}
			bomb->sr_strikes_completion->value &= ~0x7;
			bomb->sr_strikes_completion->value |= ((1 << bomb->strikes) - 1) & 0x7;

			//modules
			uint32_t completion_flags = 0;  //pattern of modules that are really completed
			uint32_t completion_all = 0;  //pattern as if all modules were completed
			uint32_t completion_mask = 0x1;  //bit for the next module
			for (struct module * m = bomb->modules; m != NULL; m = m->next) {
				if (!(m->flags & MF_COMPLETE)) {
					m->tick(bomb, m);
					if (m->flags & MF_COMPLETE) {
						printf("[bomb] \"%s\" disarmed\n", m->name);
						if (m->reset) m->reset(bomb, m);
					}
				}

				if (!(m->flags & MF_NEEDY)) {
					completion_all |= completion_mask;
					if (m->flags & MF_COMPLETE) {
						completion_flags |= completion_mask;
					}
					completion_mask <<= 1;
				}
			}

			//module completion lights
			bomb->sr_strikes_completion->value &= ~0xf8;
			bomb->sr_strikes_completion->value |= (completion_flags << 3);

			//tick tock
			if ((bomb->flags & FL_TICKTOCK) && old_secs != secs) {
				bomb->buzzer2_timer = TICKTOCK_TICKS;
				gpio_set(bomb->buzzer2, 1);
				printf("[bomb] timer=%d:%d completion=%x/%x\n", mins, secs, completion_flags, completion_all);
			}

			if (completion_flags == completion_all) {
				defuse(bomb);
				return;
			}
		} break;
		case BS_EXPLODED:
		case BS_DEFUSED:
		default:
			break;
	}
}
