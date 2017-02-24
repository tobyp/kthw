#ifndef SIMONSAYS_H_
#define SIMONSAYS_H_

#include <stdint.h>

#include "bomb.h"
#include "shift_register.h"

#define PHASE_TICKS 75
#define PHASE_DUTY_TICKS 35
#define BUTTON_FLANK_TICKS 500

struct simonsays {
	struct module mod;
	uint16_t tick_counter;
	uint16_t button_countdown;
	uint8_t expected_index;
	int8_t button_caches[4];
	uint8_t stage_count;

	uint8_t seq[6];
	struct shift_register *sr;
	uint8_t stage;

	uint32_t * button_reg;
	uint32_t button_mask;
};

void simonsays_tick(struct bomb * bomb, struct module * module);

#endif
