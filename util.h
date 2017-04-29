#ifndef UTIL_H_
#define UTIL_H_

#include <stdint.h>

#include "stm32f407vg.h"

#define NULL ((void*)0)

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
void printf(char const* format, ...);
uint32_t rnd();
uint32_t clamp(uint32_t v, uint32_t lower, uint32_t upper);

#endif
