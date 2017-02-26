#ifndef SIMONSAYS_H_
#define SIMONSAYS_H_

#include <stdint.h>

#include "bomb.h"
#include "util.h"

#define PHASE_TICKS 75
#define PHASE_DUTY_TICKS 35
#define BUTTON_FLANK_TICKS 500

struct simonsays {
	struct module module;
	struct gpio * in_btn;
	struct shreg * sr;

	uint16_t ticks;
	uint16_t button_countdown;
	uint8_t expected_index;
	int8_t button_caches[4];
	uint8_t seq[6];
	uint8_t stage_count;
	uint8_t stage;
};

int simonsays_prepare_tick(struct bomb * bomb, struct module * module);
int simonsays_tick(struct bomb * bomb, struct module * module);
void simonsays_reset(struct bomb * bomb, struct module * module);

#define SIMONSAYS_MOD_INIT {0, "simon says", &simonsays_prepare_tick, &simonsays_tick, &simonsays_reset, NULL}

#endif
