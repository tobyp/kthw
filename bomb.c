#include "bomb.h"

#include "util.h"

void bomb_init(struct bomb * bomb, struct shreg * sr_flags0, struct gpio * in_flags0, struct shreg * sr_flags1, struct gpio * in_flags1, struct shreg * timer0, struct shreg * timer1, struct shreg * timer2, struct shreg * timer3, struct shreg * strikes) {
	bomb->flags = 0;
	bomb->ticks = 10 * 60 * TICKS_PER_SEC;
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

void tick(struct bomb * bomb) {
	if (bomb->flags & BOMB_DONE) return;

	if (bomb->ticks) bomb->ticks--;
	if (bomb->ticks == 0 || bomb->strikes >= STRIKE_LIMIT) {
		print("BOOM!\n");
		bomb->flags |= BOMB_DONE;
		return;
	}

	uint8_t all_done = 1;
	for (struct module * m = bomb->modules; m != NULL; m = m->next) {
		if (!(m->flags & MOD_DONE)) {
			m->tick(bomb, m);
			all_done = 0;
		}
	}

	if (all_done) {
		print("WIN!\n");
		bomb->flags |= BOMB_DONE;
		return;
	}

	uint32_t secs = bomb->ticks / TICKS_PER_SEC;
	if (bomb->ticks % TICKS_PER_SEC == 0) {
		print("timer: "); print_uint(secs); print("\n");
	}

	bomb->sr_timer[0]->value = sevenseg_digits[secs / 1 % 10];
	//sr_write(bomb->sr_timer[1], sevenseg_digits[secs / 10 % 10]);
	//sr_write(bomb->sr_timer[2], sevenseg_digits[secs / 100 % 10]);
	bomb->sr_strikes->value = (1 << bomb->strikes) - 1;
}
