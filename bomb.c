#include "bomb.h"

#include "util.h"

void bomb_init(struct bomb * bomb, struct shreg * sr_flags0, struct gpio * in_flags0, struct shreg * sr_flags1, struct gpio * in_flags1, struct shreg * timer0, struct shreg * timer1, struct shreg * timer2, struct shreg * timer3, struct shreg * strikes) {
	bomb->flags = 0;
	bomb->flags_time = 0;
	bomb->flags_read_progress = 0;
	bomb->timer = 10 * 60 * TICKS_PER_SEC - 1;
	bomb->strikes = 0;
	bomb->sr_timer[0] = timer0;
	bomb->sr_timer[1] = timer1;
	bomb->sr_timer[2] = timer2;
	bomb->sr_timer[3] = timer3;
	bomb->sr_strikes = strikes;
	bomb->sr_flags[0] = sr_flags0;
	bomb->sr_flags[1] = sr_flags1;
	bomb->in_flags[0] = in_flags0;
	bomb->in_flags[1] = in_flags1;

	bomb->modules = NULL;
}

void bomb_add_module(struct bomb * bomb, struct module * module) {
	module->next = bomb->modules;
	bomb->modules = module;
}

void strike(struct bomb * bomb) {
	bomb->strikes++;
	print("STRIKE! ("); print_uint(bomb->strikes); print(")\n");
}

static void bomb_reset(struct bomb * bomb) {
	for (struct module * m = bomb->modules; m != NULL; m = m->next) {
		if (m->reset) {
			m->reset(bomb, m);
		}
	}
}

void bomb_prepare_tick(struct bomb * bomb) {
	uint8_t fl0 = (*bomb->in_flags[0]->reg & bomb->in_flags[0]->mask) ? 1 : 0;
	uint8_t fl1 = (*bomb->in_flags[1]->reg & bomb->in_flags[1]->mask) ? 1 : 0;

	bomb->flags = ((bomb->flags << 1) | fl0) & BOMB_EFLAGS_MASK;
	bomb->flags_time = (bomb->flags_time << 1) | fl1;
	bomb->flags_read_progress = (bomb->flags_read_progress << 1) | 1;

	if (bomb->flags_read_progress == 0xff) {
		bomb->flags |= BOMB_FLAGS_READY;

		bomb->timer = 10 * 60 * TICKS_PER_SEC; //30 * TPS * ((bomb->flags_time & 0xf8) >> 3);
		bomb->strike_limit = 3; //bomb->flags_time & 0x7;
	}
}

void tick(struct bomb * bomb) {
	if (bomb->flags & BOMB_DONE) return;

	if (bomb->flags & BOMB_READY) {
		if (bomb->timer) bomb->timer--;
		if (bomb->timer == 0 || bomb->strikes >= bomb->strike_limit) {
			bomb->flags |= BOMB_DONE;
			print("BOOM!\n");
			bomb_reset(bomb);
			return;
		}

		uint8_t all_done = 1;
		for (struct module * m = bomb->modules; m != NULL; m = m->next) {
			if (!(m->flags & MOD_DONE)) {
				if (m->tick(bomb, m)) {
					m->flags |= MOD_DONE;
					print("bomb: module \""); print(m->name); print("\" disarmed.\n");
					if (m->reset) m->reset(bomb, m);
				}
				else {
					all_done = 0;
				}
			}
		}

		if (all_done) {
			bomb->flags |= BOMB_DONE;
			print("WIN!\n");
			bomb_reset(bomb);
			return;
		}

		uint32_t secs = bomb->timer / TICKS_PER_SEC;
		if (bomb->timer % TICKS_PER_SEC == 0) {
			print("timer: "); print_uint(secs); print("\n");
		}

		uint32_t mins = secs / 60 % 100;
		secs = secs % 60;
		bomb->sr_timer[0]->value = sevenseg_digits[secs / 1 % 10];
		bomb->sr_timer[1]->value = sevenseg_digits[secs / 10 % 10];
		bomb->sr_timer[2]->value = SEVENSEG_WITH_DOT(sevenseg_digits[mins / 1 % 10]);
		bomb->sr_timer[3]->value = sevenseg_digits[mins / 10 % 10];
		bomb->sr_strikes->value = (1 << bomb->strikes) - 1;
	}
	else {
		uint8_t all_ready = 1;
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

		if (!(bomb->flags & BOMB_FLAGS_READY)) {
			bomb_prepare_tick(bomb);
			all_ready = 0;
		}

		if (all_ready) {
			bomb->flags |= BOMB_READY;
		}
	}
}
