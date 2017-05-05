#ifndef BOMB_H_
#define BOMB_H_

#include <stdint.h>

#include "util.h"

#define TICKS_PER_SEC 100  //updates per second.

/* The bomb flag and timer/strike switches are read immediately after startup. Changes after startup are ignored.
Timer/strikes: 6 bits timer (multiply by 15 seconds) and 2 bits strike limit. Setting either to 0 will immediately explode the bomb. */
enum bomb_flags {
	FL_SER_VOW = 0x1,  //the serial number contains a vowel
	FL_SER_EVEN = 0x2,  //the last digit of the serial number is even
	FL_2BATS = 0x4,  //the bomb has two or more batteries
	FL_PARPORT = 0x8,  //the bomb has a parallel port
	FL_LBL_FRK = 0x10,  //the bomb has a lit indicator labelled "FRK"
	FL_UART = 0x20,  //enable external uart
	FL_LENIENT = 0x40,  //don't punish failure with an infinite beep (just a long one)
	FL_TICKTOCK = 0x80,  //make ticking sounds every second on buzzer2
};

enum module_flags {
	MF_COMPLETE = 0x1,  //the module is completed
	MF_READY = 0x2,  //the module has finished initializing
	MF_NEEDY = 0x4,  //the module is needy (i.e. its completion is not required to defuse the bomb)
};

#define STRIKE_BUZZER_TICKS 25  //how long a strike buzzer sounds
#define PUNISH_BUZZER_TICKS 200  //how long the buzzer sounds in FL_LENIENT mode (otherwise it's infinite)
#define TICKTOCK_TICKS 1  //how long to beep every second in FL_TICKTOCK mode (otherwise not at all) 

struct bomb;

struct module {
	char const* name;
	uint8_t flags;
	void (*prepare_tick)(struct bomb * bomb, struct module * module);
	void (*tick)(struct bomb * bomb, struct module * module);
	void (*reset)(struct bomb * bomb, struct module * module);
	struct module * next;
};

#define MODULE_INIT(name) {(name), 0, NULL, NULL, NULL, NULL}
#define MODULE_INIT_FLAGS(name, flags) {(name), (flags), NULL, NULL, NULL, NULL}

struct bomb {
	struct gpio * in_flags[2];
	struct shreg * sr_flags[2];
	struct shreg * sr_strikes_completion;
	struct shreg * sr_timer[4];
	struct gpio * buzzer;
	struct gpio * buzzer2;
	struct gpio * start_in;

	uint32_t timer;  //countdown in 100s of ticks
	uint32_t timer_decrement; //timer increases (timer_decrement+100) per tick. increase this to make the timer run faster (e.g. for strikes)
	uint8_t strike_limit;
	uint32_t buzzer_timer;
	uint32_t buzzer2_timer;

	uint8_t state;
	uint8_t flags;
	uint8_t flags_time;
	uint8_t flags_read_progress;
	uint8_t strikes;
	struct module * modules;
};

void bomb_add_module(struct bomb * bomb, struct module * module);
void strike(struct bomb * bomb, struct module * module);
void explode(struct bomb * bomb, char const* cause);
void tick(struct bomb * bomb);

#endif
