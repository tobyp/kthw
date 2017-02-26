#ifndef UTIL_H_
#define UTIL_H_

#include <stdint.h>

#define NULL ((void*)0)

extern uint8_t sevenseg_digits[];
#define SEVENSEG_WITH_DOT(x) ((x) & 0xfe)

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

void print(char const* str);
void print_uint(uint32_t v);
void print_uint_hex(uint32_t v);
uint32_t rnd();

#endif
