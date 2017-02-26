#ifndef BOMB_H_
#define BOMB_H_

#include <stdint.h>

#include "util.h"

#define BOMB_SER_VOW 0x1
#define BOMB_SER_EVEN 0x2
#define BOMB_2BATS 0x4
#define BOMB_PARPORT 0x8
#define BOMB_LBL_FRK 0x10

#define BOMB_FLAGS_READY 0x20
#define BOMB_READY 0x40
#define BOMB_DONE 0x80

#define BOMB_EFLAGS_MASK (BOMB_SER_VOW|BOMB_SER_EVEN|BOMB_2BATS|BOMB_PARPORT|BOMB_LBL_FRK)

#define MOD_DONE 0x1
#define MOD_READY 0x2

#define TICKS_PER_SEC 100

struct bomb;

struct module {
	uint8_t flags;
	char const* name;
	int (*prepare_tick)(struct bomb * bomb, struct module * module);
	int (*tick)(struct bomb * bomb, struct module * module);
	void (*reset)(struct bomb * bomb, struct module * module);
	struct module * next;
};

#define MODULE_INIT(name) {0, (name), NULL, NULL, NULL, NULL}

struct bomb {
	struct gpio * in_flags[2];
	struct shreg * sr_flags[2];
	struct shreg * sr_strikes;
	struct shreg * sr_timer[4];

	uint32_t timer;
	uint8_t strike_limit;

	uint8_t flags;
	uint8_t flags_time;
	uint8_t flags_read_progress;
	uint8_t strikes;
	struct module * modules;
};

void bomb_init(struct bomb * bomb, struct shreg * sr_flags0, struct gpio * in_flags0, struct shreg * sr_flags1, struct gpio * in_flags1, struct shreg * timer0, struct shreg * timer1, struct shreg * timer2, struct shreg * timer3, struct shreg * strikes);
void bomb_add_module(struct bomb * bomb, struct module * module);
void strike(struct bomb * bomb);
void tick(struct bomb * bomb);

#endif
