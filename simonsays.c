#include "simonsays.h"

#include "util.h"

void simonsays_tick(struct bomb * bomb, struct simonsays *ss) {
	if (ss->mod.flags & MOD_DONE) return;

	uint32_t poll_index = ss->tick_counter % 4;

	if (ss->button_countdown != 0) {
		ss->button_countdown--;
		if (ss->button_countdown == 0) {
			bomb->strikes++;
		}
	}

	uint8_t button = (*ss->button_reg & ss->button_mask) >> 12;
	if (ss->button_caches[poll_index] != button) {
		if (button) {
			if (poll_index == ss->seq_in[ss->expected_index]) { //button was the expected one
				ss->expected_index++;
				if (ss->expected_index > ss->stage) {  //stage is done
					ss->expected_index = 0;
					ss->stage++;
					ss->tick_counter = (ss->stage + 1) * PHASE_TICKS;
					if (ss->stage == ss->stage_count) {
						ss->mod.flags |= MOD_DONE;
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
	ss->button_caches[poll_index] = button;

	ss->tick_counter = (ss->tick_counter + 1) % ((ss->stage + 3) * PHASE_TICKS);

	poll_index = ss->tick_counter % 4;
	uint8_t v = 1 << (poll_index + 4);

	if (ss->tick_counter < (ss->stage + 1) * PHASE_TICKS) {
		register uint32_t phase_index = ss->tick_counter / PHASE_TICKS;
		register uint32_t phase_progress = ss->tick_counter % PHASE_TICKS;
		v |= phase_progress <= PHASE_DUTY_TICKS ? (1 << ss->seq_out[phase_index]) : 0;
	}

	sr_write(ss->sr,v);
}
