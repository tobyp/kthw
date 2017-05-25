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

#ifndef UTIL_H_
#define UTIL_H_

#include <stdint.h>

#include "stm32f407vg.h"

extern uint8_t sevenseg_digits[];
#define SEVENSEG_WITH_DOT(x) ((x) | 0x80)
#define SEVENSEG_BLANK 0x00

struct gpio {
	uint32_t base;
	uint32_t mode;
	uint8_t pin;
};

static inline uint32_t gpio_get(struct gpio * p) {
	return (*GPIOx_IDR(p->base) & (1ul << p->pin)) ? 1 : 0;
}

static inline void gpio_set(struct gpio * p, uint32_t v) {
	if (v) {
		*GPIOx_ODR(p->base) |= (1ul << p->pin);
	}
	else {
		*GPIOx_ODR(p->base) &= ~(1ul << p->pin);
	}
}

struct adc {
	uint8_t channel;
	uint16_t value;
};

//QA=MSB, QH=LSB
struct shreg {
	struct gpio * ser;
	uint8_t value;
	uint8_t value_cache; //private to writeback loop
};

struct lcd {
	struct gpio * lcd_rs;
	struct gpio * lcd_en;
	struct shreg * lcd_data;
	uint8_t mode, cmd;
};

#define LCD_CMD 0
#define LCD_DATA 1
#define LCD_NONE 2
#define LCD_CMD_CURSOR(x, y) ((x)*64+(y)+128)

void delay(uint32_t ms);
uint32_t rnd();
uint32_t rnd_range(uint32_t min, uint32_t max);
uint32_t clamp(uint32_t v, uint32_t lower, uint32_t upper);

extern uint8_t uart_enabled;
void printf(char const* format, ...);

#endif
