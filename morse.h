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

#ifndef MORSE_H_
#define MORSE_H_

#include <stdint.h>

#include "bomb.h"
#include "util.h"

#define TICKS_PER_DOT 50

struct morse_seq {
	char const* word;
	/* A dot is a single 1-bit. A dash is three 1-bits.
	A pause between dots/dashes is a single 0-bit.
	A pause between letters is three 0-bits.
	The pause between repetitions of the word is 7 0-bits. */
	uint8_t dots[32];
	uint8_t bits;
	uint16_t freq;
};

struct morse {
	struct module module;
	struct gpio * out_led;
	struct gpio * in_btn;
	struct adc * adc;
	struct shreg * freq[4];

	uint16_t ticks;
	struct morse_seq * seq;
	uint8_t button_cache;
};

void morse_prepare_tick(struct bomb * bomb, struct module * module);
void morse_tick(struct bomb * bomb, struct module * module);
void morse_reset(struct bomb * bomb, struct module * module);

#define MORSE_MOD_INIT {"morse", 0, &morse_prepare_tick, &morse_tick, &morse_reset, NULL}
#endif
