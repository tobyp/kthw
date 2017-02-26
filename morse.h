#ifndef MORSE_H_
#define MORSE_H_

#include <stdint.h>

#include "bomb.h"
#include "util.h"

#define TICKS_PER_DOT 50

struct morse_seq {
	uint8_t dots[32];
	uint8_t bits;
	uint16_t freq;
};

struct morse {
	struct module mod;
	uint16_t ticks;
	struct morse_seq * seq;

	uint8_t button_cache;

	struct gpio * out_led;
	struct gpio * in_btn;
	struct shreg * freq[4];
	struct adc * adc;
};

void morse_init(struct bomb * bomb, struct morse * morse, struct gpio * out_led, struct gpio * in_btn, struct adc * adc, struct shreg * freq0, struct shreg * freq1, struct shreg * freq2, struct shreg * freq3);
void morse_tick(struct bomb * bomb, struct module * module);

#endif
