#ifndef UTIL_H_
#define UTIL_H_

#include <stdint.h>

#define NULL ((void*)0)

extern uint8_t sevenseg_digits[];
#define SEVENSEG_WITH_DOT(x) ((x) & 0xfe)
#define SEVENSEG_BLANK 0xff

struct gpio {
	uint32_t * reg;
	uint32_t mask;
};

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
void print(char const* str);
void print_uint(uint32_t v);
void print_uint_hex(uint32_t v);
uint32_t rnd();
uint32_t clamp(uint32_t v, uint32_t lower, uint32_t upper);

#endif
