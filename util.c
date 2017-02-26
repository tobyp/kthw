#include "util.h"

#include "stm32f407vg.h"

uint8_t sevenseg_digits[] = {0x03,0x9f,0x25,0x0d,0x99,0x49,0x41,0x1f,0x01,0x09};

void print_uint(uint32_t v) {
	char digits[10] = {0};
	uint8_t i;
	for (i=10; v > 0;) {
		digits[--i] = v % 10;
		v /= 10;
	}
	if (i==10) i = 9;
	for (; i<10; ++i) {
		*USARTx_DR(UART4_BASE) = '0' + digits[i];
		while ((*USARTx_SR(UART4_BASE) & USART_SR_TXE) == 0) {
			__asm__("nop");
		}
	}
}

void print(char const* str) {
	while (*str) {
		*USARTx_DR(UART4_BASE) = *str;
		while ((*USARTx_SR(UART4_BASE) & USART_SR_TXE) == 0) {
			__asm__("nop");
		}
		str++;
	}
}

uint32_t rnd() {
	return 4;
}
