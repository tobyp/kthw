/* KTHW - Hardware Clone of Keep Talking and Nobody Explodes
Copyright (C) 2017 Toby P., Thomas H.
Copyright (C) 2019 Toby P.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include "morse.h"

/* The morse module will blink a random word at you in the eponymous code at an
excruciatingly slow speed, and expects you to transmit a reply on a frequency
dependent on that word. */

#include "morse.words.generated.c"

void morse_prepare_tick(struct bomb * bomb, struct module * module) {
	struct morse * morse = (struct morse *)module;

	morse->seq = &morse_seqs[rnd_range(0, sizeof(morse_seqs) / sizeof(struct morse_seq))];
	printf("[%s] word=\"%s\" freq=%d\n", module->name, morse->seq->word, morse->seq->freq);

	module->flags |= MF_READY;
}

void morse_tick(struct bomb * bomb, struct module * module) {
	struct morse * morse = (struct morse *)module;

	morse->ticks = (morse->ticks + 1) % (TICKS_PER_DOT * morse->seq->bits);
	uint32_t cursor = morse->ticks / TICKS_PER_DOT;

	if (morse->seq->dots[cursor / 8] & (0x80 >> (cursor % 8))) {
		gpio_set(morse->out_led, 1);
	}
	else {
		gpio_set(morse->out_led, 0);
	}

	uint16_t freq = morse->adc->value * 120 / 4096 + 3482;
	morse->freq[0]->value = sevenseg_digits[freq / 1 % 10];
	morse->freq[1]->value = sevenseg_digits[freq / 10 % 10];
	morse->freq[2]->value = sevenseg_digits[freq / 100 % 10];
	morse->freq[3]->value = sevenseg_digits[freq / 1000 % 10];

	uint8_t value = (gpio_get(morse->in_btn)) ? 1 : 0;
	if (morse->button_cache != value) {
		morse->button_cache = value;
		if (value) {
			if (freq >= morse->seq->freq - 1 && freq <= morse->seq->freq + 1) {
				module->flags |= MF_COMPLETE;
				return;
			}
			else {
				strike(bomb, module);
				morse->ticks = 0;
			}
		}
	}
}

void morse_reset(struct bomb * bomb, struct module * module) {
	struct morse * morse = (struct morse *)module;

	gpio_set(morse->out_led, 0);
	morse->freq[0]->value = SEVENSEG_BLANK;
	morse->freq[1]->value = SEVENSEG_BLANK;
	morse->freq[2]->value = SEVENSEG_BLANK;
	morse->freq[3]->value = SEVENSEG_BLANK;
}
