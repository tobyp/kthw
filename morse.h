#ifndef MORSE_H_
#define MORSE_H_

#include <stdint.h>

#include "bomb.h"
#include "util.h"

#define TICKS_PER_DOT 50

struct morse_seq {
	char const* word;
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

int morse_prepare_tick(struct bomb * bomb, struct module * module);
int morse_tick(struct bomb * bomb, struct module * module);
void morse_reset(struct bomb * bomb, struct module * module);

#define MORSE_MOD_INIT {0, "morse", &morse_prepare_tick, &morse_tick, &morse_reset, NULL}
#endif
