#include "simonsays.h"

#include "util.h"

#define BLUE	0
#define YELLOW	1
#define RED		2
#define GREEN	3

//BLUE YELLOW RED GREEN
static uint8_t expectations[2][3][4] = {
	{
		{YELLOW,	RED,		BLUE,		GREEN,		},
		{BLUE,		GREEN,		RED,		YELLOW,		},
		{GREEN,		RED,		YELLOW,		BLUE,		},
	},
	{
		{RED,		GREEN,		BLUE,		YELLOW,		},
		{GREEN,		RED,		YELLOW,		BLUE,		},
		{RED,		BLUE,		GREEN,		YELLOW,		},
	}
};

int simonsays_prepare_tick(struct bomb * bomb, struct module * module) {
	struct simonsays * simonsays = (struct simonsays *)module;

	simonsays->stage_count = 4 + rnd() % 2;
	printf("[%s] stages=%d sequence=[", module->name, simonsays->stage_count);
	for (uint8_t i=0; i<simonsays->stage_count; ++i) {
		simonsays->seq[i] = (rnd() + i) % 4;
		printf("%d,", simonsays->seq[i]);
	}
	printf("\b]\n");

	return 1;
}

int simonsays_tick(struct bomb * bomb, struct module * module) {
	struct simonsays * simonsays = (struct simonsays *)module;

	uint32_t poll_button = simonsays->ticks % 4;

	if (simonsays->button_countdown != 0) {
		simonsays->button_countdown--;
		if (simonsays->button_countdown == 0) {
			strike(bomb);
		}
	}

	uint8_t button = (*simonsays->in_btn->reg & simonsays->in_btn->mask) ? 1 : 0;
	if (simonsays->button_caches[poll_button] != button) {
		simonsays->button_caches[poll_button] = button;
		if (button) {
			uint8_t expected_button = expectations[bomb->flags & BOMB_SER_VOW ? 1 : 0][bomb->strikes % 3][simonsays->seq[simonsays->expected_index]];
			if (poll_button == expected_button) { //button was the expected one
				simonsays->expected_index++;
				if (simonsays->expected_index > simonsays->stage) {  //stage is done
					simonsays->stage++;
					simonsays->ticks = (simonsays->stage + 1) * PHASE_TICKS;
					simonsays->expected_index = 0;
					simonsays->button_countdown = 0;
					if (simonsays->stage == simonsays->stage_count) {
						return 1;
					}
				}
				else {
					simonsays->ticks = (simonsays->stage + 1) * PHASE_TICKS;
					simonsays->button_countdown = BUTTON_FLANK_TICKS;
				}
			}
			else {
				strike(bomb);
				simonsays->sr->value = 0;
				simonsays->stage = 0;
				simonsays->expected_index = 0;
				simonsays->button_countdown = 0;
			}
		}
	}

	simonsays->ticks = (simonsays->ticks + 1) % ((simonsays->stage + 3) * PHASE_TICKS);

	poll_button = simonsays->ticks % 4;
	uint8_t v = 1 << (poll_button + 4);

	if (simonsays->ticks < (simonsays->stage + 1) * PHASE_TICKS) {
		register uint32_t phase_index = simonsays->ticks / PHASE_TICKS;
		register uint32_t phase_progress = simonsays->ticks % PHASE_TICKS;
		v |= phase_progress <= PHASE_DUTY_TICKS ? (1 << simonsays->seq[phase_index]) : 0;
	}

	simonsays->sr->value = v;
	return 0;
}

void simonsays_reset(struct bomb * bomb, struct module * module) {
	struct simonsays * simonsays = (struct simonsays *)module;

	simonsays->sr->value = 0;
}