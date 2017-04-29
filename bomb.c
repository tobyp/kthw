#include "bomb.h"

#include "util.h"

#define BOMB_FLAGS_READY 0x1
#define BOMB_READY 0x2
#define BOMB_DONE 0x4

void bomb_init(struct bomb * bomb, struct shreg * sr_flags0, struct gpio * in_flags0, struct shreg * sr_flags1, struct gpio * in_flags1, struct shreg * timer0, struct shreg * timer1, struct shreg * timer2, struct shreg * timer3, struct shreg * strikes) {
	bomb->sr_timer[0] = timer0;
	bomb->sr_timer[1] = timer1;
	bomb->sr_timer[2] = timer2;
	bomb->sr_timer[3] = timer3;
	bomb->sr_strikes_completion = strikes;
	bomb->sr_flags[0] = sr_flags0;
	bomb->sr_flags[1] = sr_flags1;
	bomb->in_flags[0] = in_flags0;
	bomb->in_flags[1] = in_flags1;

	bomb->timer = 10 * 60 * TICKS_PER_SEC - 1;
	bomb->buzzer_timer = 0;

	bomb->flags = 0;
	bomb->flags_time = 0;
	bomb->flags_read_progress = 0;
	bomb->strikes = 0;

	bomb->modules = NULL;
}

void bomb_add_module(struct bomb * bomb, struct module * module) {
	module->next = bomb->modules;
	bomb->modules = module;
}

void strike(struct bomb * bomb, struct module * module) {
	bomb->strikes++;
	bomb->buzzer_timer = STRIKE_BUZZER_TICKS;
	gpio_set(bomb->buzzer, 1);
	printf("[bomb] strike %d from %s\n", bomb->strikes, module->name);
}

void explode(struct bomb * bomb) {
	bomb->strikes = bomb->strike_limit;
}

static void bomb_reset(struct bomb * bomb) {
	for (struct module * m = bomb->modules; m != NULL; m = m->next) {
		if (m->reset) {
			m->reset(bomb, m);
		}
	}
}

void bomb_prepare_tick(struct bomb * bomb) {
	uint8_t fl0 = gpio_get(bomb->in_flags[0]);
	uint8_t fl1 = gpio_get(bomb->in_flags[1]);

	if (bomb->flags_read_progress) {
		bomb->flags = (bomb->flags << 1) | fl0;
		bomb->flags_time = (bomb->flags_time << 1) | fl1;
	}

	if (bomb->flags_read_progress == 0xff) {
		bomb->flags_sw |= BOMB_FLAGS_READY;

		bomb->timer = /* 10 * 60 * TICKS_PER_SEC; //*/ 15 * ((bomb->flags_time >> 2) & 0x3f) * TICKS_PER_SEC;
		bomb->strike_limit = /* 3; //*/bomb->flags_time & 0x03;

		printf("[bomb] timer=%d strikelimit=%d flags_time=%x flags=%x\n", bomb->timer, bomb->strike_limit, bomb->flags_time, bomb->flags);
	}
	else {
		bomb->sr_flags[0]->value = bomb->sr_flags[1]->value = bomb->flags_read_progress + 1;
		bomb->flags_read_progress = (bomb->flags_read_progress << 1) | 1;
	}
}

void tick(struct bomb * bomb) {
	if (bomb->flags_sw & BOMB_DONE) return;

	if (bomb->flags_sw & BOMB_READY) {
		if (bomb->timer) bomb->timer--;
		if (bomb->timer == 0 || bomb->strikes >= bomb->strike_limit) {
			bomb->flags_sw |= BOMB_DONE;
			bomb->sr_strikes_completion->value = 0x7;
			gpio_set(bomb->buzzer, 1);
			printf("[bomb] explode\n");
			bomb_reset(bomb);
			return;
		}

		if (bomb->buzzer_timer > 0) {
			bomb->buzzer_timer--;
			if (bomb->buzzer_timer == 0) {
				gpio_set(bomb->buzzer, 0);
			}
		}

		uint32_t completion_flags = 0;
		uint32_t completion_all = 0;
		uint32_t completion_mask = 0x1;
		for (struct module * m = bomb->modules; m != NULL; m = m->next) {
			if (!(m->flags & MOD_DONE)) {
				if (m->tick(bomb, m)) {
					m->flags |= MOD_DONE;
					printf("[bomb] \"%s\" disarmed\n", m->name);
					if (m->reset) m->reset(bomb, m);
				}
			}

			if (!(m->flags & MOD_NEEDY)) {
				completion_all |= completion_mask;
				if (m->flags & MOD_DONE) {
					completion_flags |= completion_mask;
				}
				completion_mask <<= 1;
			}
		}

		if (completion_flags == completion_all) {
			bomb->flags_sw |= BOMB_DONE;
			bomb->buzzer_timer = 0;
			gpio_set(bomb->buzzer, 0);
			printf("[bomb] defused\n");
			bomb_reset(bomb);
			bomb->sr_strikes_completion->value = (((1 << bomb->strikes) - 1) & 0x7) | (completion_flags << 3);
			return;
		}

		uint32_t secs = bomb->timer / TICKS_PER_SEC;
		if (bomb->timer % TICKS_PER_SEC == 0) {
			printf("[bomb] timer=%d completion=%x/%x\n", secs, completion_flags, completion_all);
		}

		uint32_t mins = secs / 60 % 100;
		secs = secs % 60;
		bomb->sr_timer[0]->value = sevenseg_digits[secs / 1 % 10];
		bomb->sr_timer[1]->value = sevenseg_digits[secs / 10 % 10];
		bomb->sr_timer[2]->value = SEVENSEG_WITH_DOT(sevenseg_digits[mins / 1 % 10]);
		bomb->sr_timer[3]->value = sevenseg_digits[mins / 10 % 10];
		bomb->sr_strikes_completion->value = (((1 << bomb->strikes) - 1) & 0x7) | (completion_flags << 3);
	}
	else {
		uint32_t all_ready = 1;
		for (struct module * m = bomb->modules; m != NULL; m = m->next) {
			if (!(m->flags & MOD_READY)) {
				if (m->prepare_tick) {
					if (m->prepare_tick(bomb, m)) {
						m->flags |= MOD_READY;
					}
					else {
						all_ready = 0;
					}
				}
				else {
					m->flags |= MOD_READY;
				}
			}
		}

		if (!(bomb->flags_sw & BOMB_FLAGS_READY)) {
			bomb_prepare_tick(bomb);
			all_ready = 0;
		}

		if (all_ready) {
			bomb->flags_sw |= BOMB_READY;
		}
	}
}
