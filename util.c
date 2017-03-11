#include "util.h"

#include <stdarg.h>

#include "stm32f407vg.h"

uint8_t sevenseg_digits[] = {0x03,0x9f,0x25,0x0d,0x99,0x49,0x41,0x1f,0x01,0x09};
static char hexits[] = "0123456789abcdef";

void delay(uint32_t ms) {
	ms *= 266;
	while (ms > 0) {
		ms--;
	}
}

static inline void put(char c) {
	*USARTx_DR(UART4_BASE) = c;
	while ((*USARTx_SR(UART4_BASE) & USART_SR_TXE) == 0) {
		__asm__("nop");
	}
}

static inline void print_uint(uint32_t v) {
	uint8_t digits[10] = {0};
	uint8_t i;
	for (i=10; v > 0;) {
		digits[--i] = v % 10;
		v /= 10;
	}
	if (i==10) i = 9;
	for (; i<10; ++i) {
		*USARTx_DR(UART4_BASE) = hexits[digits[i]];
		while ((*USARTx_SR(UART4_BASE) & USART_SR_TXE) == 0) {
			__asm__("nop");
		}
	}
}

static inline void print_uint_hex(uint32_t v) {
	uint8_t digits[8] = {0};
	uint8_t i;
	for (i=8; v > 0;) {
		digits[--i] = v % 16;
		v /= 16;
	}
	if (i==8) i = 7;
	for (; i<8; ++i) {
		*USARTx_DR(UART4_BASE) = hexits[digits[i]];
		while ((*USARTx_SR(UART4_BASE) & USART_SR_TXE) == 0) {
			__asm__("nop");
		}
	}
}

static inline void print(char const* str) {
	while (*str) {
		*USARTx_DR(UART4_BASE) = *str;
		while ((*USARTx_SR(UART4_BASE) & USART_SR_TXE) == 0) {
			__asm__("nop");
		}
		str++;
	}
}

static void vprintf(char const* format, va_list args) {
	while (*format) {
		if (*format == '%') {
			format++;
			switch (*format) {
				case '%':
					put('%');
					break;
				case 's': {
					char const* arg = va_arg(args, char const*);
					print(arg);
					} break;
				case 'x': {
					uint32_t arg = va_arg(args, uint32_t);
					print_uint_hex(arg);
					} break;
				case 'd': {
					uint32_t arg = va_arg(args, uint32_t);
					print_uint(arg);
					} break;
			}
		}
		else {
			put(*format);
		}
		format++;
	}
}

void printf(char const* format, ...) {
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}

uint32_t rnd() {
	while ((*RNG_SR & RNG_SR_DRDY) == 0) ;
	return *RNG_DR;
}

uint32_t clamp(uint32_t v, uint32_t lower, uint32_t upper) {
	return (v < lower ? lower : (v > upper ? upper : v));
}
