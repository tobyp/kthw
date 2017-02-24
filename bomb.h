#ifndef BOMB_H_
#define BOMB_H_

#include <stdint.h>

#include "shift_register.h"

#define BOMB_DONE 0x1
#define STRIKE_LIMIT 3
#define TICKS_PER_SEC 100
#define MOD_DONE 0x1

struct module {
	uint8_t flags;
	struct module * next;
};

struct bomb {
	uint8_t flags;
	uint32_t ticks;
	uint8_t strikes;

	struct shift_register * sr_timer[3];
	struct shift_register * sr_strikes;

	struct module * modules;
};

void strike(struct bomb * bomb);
int bomb_tick(struct bomb * bomb);

#endif
