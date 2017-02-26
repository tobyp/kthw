#ifndef BOMB_H_
#define BOMB_H_

#include <stdint.h>

#include "util.h"

#define BOMB_DONE 0x1
#define BOMB_SER_VOW 0x2
#define BOMB_SER_EVEN 0x4
#define BOMB_2BATS 0x8
#define BOMB_PARPORT 0x10
#define BOMB_LBL_FRK 0x20

#define STRIKE_LIMIT 3
#define TICKS_PER_SEC 100
#define MOD_DONE 0x1

struct bomb;

struct module {
	uint8_t flags;
	void (*tick)(struct bomb * bomb, struct module * module);
	struct module * next;
};

struct bomb {
	uint8_t flags;
	uint32_t ticks;
	uint8_t strikes;

	struct shreg * sr_timer[4];
	struct shreg * sr_strikes;
	struct shreg * sr_flags[2];
	struct gpio * in_flags[2];

	struct module * modules;
};

void bomb_init(struct bomb * bomb, struct shreg * sr_flags0, struct gpio * in_flags0, struct shreg * sr_flags1, struct gpio * in_flags1, struct shreg * timer0, struct shreg * timer1, struct shreg * timer2, struct shreg * timer3, struct shreg * strikes);
void bomb_add_module(struct bomb * bomb, struct module * module);
void strike(struct bomb * bomb);
void tick(struct bomb * bomb);

#endif
