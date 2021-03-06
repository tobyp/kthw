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

#include <stdarg.h>

#include "util.h"

uint8_t sevenseg_digits[] = {0x7e, 0x48, 0x3d, 0x6d, 0x4b, 0x67, 0x77, 0x4c, 0x7f, 0x6f};
static char hexits[] = "0123456789abcdef";

void delay(uint32_t ms) {
	ms *= 266;
	while (ms > 0) {
		ms--;
	}
}

uint8_t uart_enabled = 0; //set to one once uart is ready

static inline void put(char c) {
	if (!uart_enabled) return;
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
				default: //also handles the %\0 case
					print("<WARNING: unknown %specifier '");
					put(*format);
					print("'>");
					break;
			}
		}
		else {
			put(*format);
		}
		format++;
	}
}

void printf(char const* format, ...) {
	if (!uart_enabled) return; //optimization
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}

uint32_t rnd() {
	while ((*RNG_SR & RNG_SR_DRDY) == 0) ;
	return *RNG_DR;
}

uint32_t rnd_range(uint32_t min, uint32_t max) {
	return min + rnd() % (max - min);
}

uint32_t clamp(uint32_t v, uint32_t lower, uint32_t upper) {
	return (v < lower ? lower : (v > upper ? upper : v));
}
