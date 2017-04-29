#include "simonsays.h"

#include "util.h"

#define BTN_BLUE	0
#define BTN_YELLOW	1
#define BTN_RED		2
#define BTN_GREEN	3

#define LED_GREEN	0
#define LED_BLUE	1
#define LED_RED		2
#define LED_YELLOW	3

//buttons: BLUE YELLOW RED GREEN
//lights:  GREEN BLUE RED YELLOW
static uint8_t expectations[2][3][4] = {
	//	LED_GREEN		LED_BLUE		LED_RED			LED_YELLOW
	{
		{BTN_YELLOW,	BTN_RED,		BTN_BLUE,		BTN_GREEN	},
		{BTN_BLUE,		BTN_GREEN,		BTN_YELLOW,		BTN_RED		},
		{BTN_YELLOW,	BTN_RED,		BTN_GREEN,		BTN_BLUE	},
	},
	{
		{BTN_GREEN,		BTN_YELLOW,		BTN_BLUE,		BTN_RED,	},
		{BTN_YELLOW,	BTN_BLUE,		BTN_RED,		BTN_GREEN,	},
		{BTN_BLUE,		BTN_GREEN,		BTN_YELLOW,		BTN_RED,	},
	}
};

static inline uint8_t simonsays_expected(struct bomb * bomb, struct simonsays * simonsays) {
	return expectations[(bomb->flags & FL_SER_VOW) ? 0 : 1][bomb->strikes % 3][simonsays->seq[simonsays->expected_index]];
}

int simonsays_prepare_tick(struct bomb * bomb, struct module * module) {
	struct simonsays * simonsays = (struct simonsays *)module;

	simonsays->stage_count = 4 + rnd() % 2;
	printf("[%s] stage=0/%d sequence=[", module->name, simonsays->stage_count);
	for (uint8_t i=0; i<simonsays->stage_count; ++i) {
		simonsays->seq[i] = rnd() % 4;
		printf("%d,", simonsays->seq[i]);
	}
	printf("\b] expected=%d\n", simonsays_expected(bomb, simonsays));

	return 1;
}

int simonsays_tick(struct bomb * bomb, struct module * module) {
	struct simonsays * simonsays = (struct simonsays *)module;

	uint32_t poll_button = simonsays->ticks % 4;

	if (simonsays->button_countdown != 0) {
		simonsays->button_countdown--;
		if (simonsays->button_countdown == 0) {
			strike(bomb, module);
		}
	}

	uint8_t button = gpio_get(simonsays->in_btn);
	if (simonsays->button_caches[poll_button] != button) {
		simonsays->button_caches[poll_button] = button;
		if (button) {
			uint8_t expected_button = simonsays_expected(bomb, simonsays);
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
				strike(bomb, module);
				simonsays->sr->value = 0;
				simonsays->stage = 0;
				simonsays->expected_index = 0;
				simonsays->button_countdown = 0;
			}
			printf("[%s] stage=%d/%d expected=%d\n", module->name, simonsays->stage, simonsays->stage_count, simonsays_expected(bomb, simonsays));
		}
	}

	simonsays->ticks = (simonsays->ticks + 1) % ((simonsays->stage + 3) * PHASE_TICKS);

	poll_button = simonsays->ticks % 4;
	uint8_t v = 1 << (poll_button + 4);

	if (simonsays->ticks < (simonsays->stage + 1) * PHASE_TICKS) {
		register uint32_t phase_index = simonsays->ticks / PHASE_TICKS;
		register uint32_t phase_progress = simonsays->ticks % PHASE_TICKS;
		v |= (phase_progress <= PHASE_DUTY_TICKS) ? (1 << simonsays->seq[phase_index]) : 0;
	}

	simonsays->sr->value = v;
	return 0;
}

void simonsays_reset(struct bomb * bomb, struct module * module) {
	struct simonsays * simonsays = (struct simonsays *)module;

	simonsays->sr->value = 0;
}