#include "morse.h"
#include "util.h"

void morse_tick(struct bomb * bomb, struct module * mod) {
	struct morse * morse = (struct morse *)mod;

	morse->ticks = (morse->ticks + 1) % (TICKS_PER_DOT * morse->seq_units);
	uint32_t dots = morse->ticks / TICKS_PER_DOT;

	if (morse->seq[dots / 8] & (0x80 >> (dots % 8))) {
		*morse->led_reg |= morse->led_mask;
	}
	else {
		*morse->led_reg &= ~morse->led_mask;
	}

	//read freq_in
	morse->freq_set = morse->freq_expect;

	uint8_t value = (*morse->button_reg & morse->button_mask) ? 1 : 0;
	if (value) {
		if (morse->freq_set == morse->freq_expect) {
			print("morse: disarmed\n");
			mod->flags |= MOD_DONE;
			*morse->led_reg &= ~morse->led_mask;
			return;
		}
		else {
			strike(bomb);
			morse->ticks = 0;
		}
	}
}
