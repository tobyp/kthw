#include "simonsays.h"

#include "util.h"

#define BLUE	0
#define YELLOW	1
#define RED		2
#define GREEN	3

static uint8_t expectations[2][3][4] = {
	{
		{BLUE, YELLOW, GREEN, RED},
		{RED, BLUE, YELLOW, GREEN},
		{YELLOW, GREEN, BLUE, RED},
	},
	{
		{BLUE, RED, YELLOW, GREEN},
		{YELLOW, GREEN, BLUE, RED},
		{GREEN, RED, YELLOW, BLUE},
	}
};

void simonsays_tick(struct bomb * bomb, struct module * mod) {
	struct simonsays * ss = (struct simonsays *)mod;

	uint32_t poll_button = ss->tick_counter % 4;

	if (ss->button_countdown != 0) {
		ss->button_countdown--;
		if (ss->button_countdown == 0) {
			bomb->strikes++;
		}
	}

	uint8_t button = (*ss->button_reg & ss->button_mask) >> 12;
	if (ss->button_caches[poll_button] != button) {
		if (button) {
			uint8_t expected_button = expectations[bomb->flags & BOMB_SERIAL_VOWEL ? 1 : 0][bomb->strikes % 3][ss->seq[ss->expected_index]];
			if (poll_button == expected_button) { //button was the expected one
				ss->expected_index++;
				if (ss->expected_index > ss->stage) {  //stage is done
					ss->expected_index = 0;
					ss->stage++;
					ss->tick_counter = (ss->stage + 1) * PHASE_TICKS;
					if (ss->stage == ss->stage_count) {
						mod->flags |= MOD_DONE;
						sr_write(ss->sr, 0);
						print("simon_says: disarmed\n");
						return;
					}
				}
				else {
					ss->button_countdown = BUTTON_FLANK_TICKS;
				}
			}
			else {
				strike(bomb);
				sr_write(ss->sr, 0);
				ss->stage = 0;
				ss->expected_index = 0;
				ss->button_countdown = 0;
			}
		}
	}
	ss->button_caches[poll_button] = button;

	ss->tick_counter = (ss->tick_counter + 1) % ((ss->stage + 3) * PHASE_TICKS);

	poll_button = ss->tick_counter % 4;
	uint8_t v = 1 << (poll_button + 4);

	if (ss->tick_counter < (ss->stage + 1) * PHASE_TICKS) {
		register uint32_t phase_index = ss->tick_counter / PHASE_TICKS;
		register uint32_t phase_progress = ss->tick_counter % PHASE_TICKS;
		v |= phase_progress <= PHASE_DUTY_TICKS ? (1 << ss->seq[phase_index]) : 0;
	}

	sr_write(ss->sr,v);
}
