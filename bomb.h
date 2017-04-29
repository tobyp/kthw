#ifndef BOMB_H_
#define BOMB_H_

#include <stdint.h>

#include "util.h"

//bomb flags
#define FL_SER_VOW 0x1
#define FL_SER_EVEN 0x2
#define FL_2BATS 0x4
#define FL_PARPORT 0x8
#define FL_LBL_FRK 0x10

//bomb timer/strikes [time * 15s:6bit] [strikes:2bit]

#define MOD_DONE 0x1
#define MOD_READY 0x2
#define MOD_NEEDY 0x4

#define STRIKE_BUZZER_TICKS 25
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
	struct shreg * sr_strikes_completion;
	struct shreg * sr_timer[4];
	struct gpio * buzzer;

	uint32_t timer;
	uint8_t strike_limit;
	uint16_t buzzer_timer;

	uint8_t flags;
	uint8_t flags_sw;
	uint8_t flags_time;
	uint8_t flags_read_progress;
	uint8_t strikes;
	struct module * modules;
};

void bomb_init(struct bomb * bomb, struct shreg * sr_flags0, struct gpio * in_flags0, struct shreg * sr_flags1, struct gpio * in_flags1, struct shreg * timer0, struct shreg * timer1, struct shreg * timer2, struct shreg * timer3, struct shreg * strikes);
void bomb_add_module(struct bomb * bomb, struct module * module);
void strike(struct bomb * bomb, struct module * module);
void explode(struct bomb * bomb);
void tick(struct bomb * bomb);

#endif
