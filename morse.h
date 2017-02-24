#ifndef MORSE_H_
#define MORSE_H_

#include <stdint.h>

#include "bomb.h"
#include "shift_register.h"

#define TICKS_PER_DOT 50

#define MORSE_SEQ_SLICK {0xa8, 0xba, 0x8a, 0x3a, 0xe8, 0xeb, 0x80}, 7*8
#define MORSE_FREQ_SLICK 522

struct morse {
	struct module mod;
	uint16_t ticks;
	uint8_t seq[13]; //longest letter is J/Q/X; a word with 6 of those takes 100 units
	uint8_t seq_units;

	uint16_t freq_expect;
	uint16_t freq_set;

	uint32_t * adc_cr;
	uint32_t * adc_data;
	uint32_t * led_reg;
	uint32_t led_mask;
	uint32_t * button_reg;
	uint32_t button_mask;
};

void morse_tick(struct bomb * bomb, struct module * module);

#endif
