/* KTHW - Hardware Clone of Keep Talking and Nobody Explodes
Copyright (C) 2017 Toby P., Thomas H.

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

static struct morse_seq morse_seqs[] = {
	{"shell", {0xa8, 0xaa, 0x22, 0xea, 0x2e, 0xa0, 0x0}, 50, 3505},
	{"halls", {0xaa, 0x2e, 0x2e, 0xa2, 0xea, 0x2a, 0x0}, 54, 3515},
	{"slick", {0xa8, 0xba, 0x8a, 0x3a, 0xe8, 0xeb, 0x80}, 56, 3522},
	{"trick", {0xe2, 0xe8, 0xa3, 0xae, 0x8e, 0xb8, 0x0}, 52, 3532},
	{"boxes", {0xea, 0x8e, 0xee, 0x3a, 0xb8, 0x8a, 0x80}, 56, 3535},
	{"leaks", {0xba, 0x88, 0xb8, 0xeb, 0x8a, 0x80}, 48, 3542},
	{"strobe", {0xa8, 0xe2, 0xe8, 0xee, 0xe3, 0xaa, 0x20, 0x0}, 58, 3545},
	{"bistro", {0xea, 0x8a, 0x2a, 0x38, 0xba, 0x3b, 0xb8, 0x0}, 60, 3552},
	{"flick", {0xae, 0x8b, 0xa8, 0xa3, 0xae, 0x8e, 0xb8, 0x0}, 60, 3555},
	{"bombs", {0xea, 0x8e, 0xee, 0x3b, 0x8e, 0xa8, 0xa8, 0x0}, 60, 3565},
	{"break", {0xea, 0x8b, 0xa2, 0x2e, 0x3a, 0xe0, 0x0}, 50, 3572},
	{"brick", {0xea, 0x8b, 0xa2, 0x8e, 0xba, 0x3a, 0xe0, 0x0}, 58, 3575},
	{"steak", {0xa8, 0xe2, 0x2e, 0x3a, 0xe0, 0x0}, 42, 3582},
	{"sting", {0xa8, 0xe2, 0x8e, 0x8e, 0xe8, 0x0}, 44, 3592},
	{"vector", {0xab, 0x88, 0xeb, 0xa3, 0x8e, 0xee, 0x2e, 0x80}, 64, 3595},
	{"beats", {0xea, 0x88, 0xb8, 0xe2, 0xa0, 0x0}, 42, 3600},
};

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
