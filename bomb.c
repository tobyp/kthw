#include "bomb.h"

#include "util.h"

static uint8_t sevenseg_digits[] = {0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xFA,0xE0,0xFE,0xF6};

void strike(struct bomb * bomb) {
	bomb->strikes++;
	print("STRIKE! ("); print_uint(bomb->strikes); print(")\n");
}

int bomb_tick(struct bomb * bomb) {
	if (bomb->flags & BOMB_DONE) return 1;

	if (bomb->ticks) bomb->ticks--;
	if (bomb->ticks == 0 || bomb->strikes >= STRIKE_LIMIT) {
		print("BOOM!\n");
		bomb->flags |= BOMB_DONE;
		return 1;
	}
	uint32_t secs = bomb->ticks / TICKS_PER_SEC;
	if (bomb->ticks % TICKS_PER_SEC == 0) {
		print("timer: "); print_uint(secs); print("\n");
	}

	uint8_t all_done = 1;
	for (struct module * m = bomb->modules; m != NULL; m = m->next) {
		if (!(m->flags & MOD_DONE)) {
			all_done = 0;
			break;
		}
	}

	if (all_done) {
		print("WIN!\n");
		bomb->flags |= BOMB_DONE;
		return 1;
	}
	
	//sr_write(bomb->sr_timer[0], sevenseg_digits[secs / 1 % 10]);
	//sr_write(bomb->sr_timer[1], sevenseg_digits[secs / 10 % 10]);
	//sr_write(bomb->sr_timer[2], sevenseg_digits[secs / 100 % 10]);
	//sr_write(bomb->sr_strikes, (1 << bomb->strikes) - 1);
	//count finished modules
	return 0;
}
