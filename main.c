 #include <stdint.h>

#include "stm32f407vg.h"

/*#define MASK_SER 0x100ul	//B8
#define MASK_SRCLK 0x200ul	//B9
#define MASK_RCLK 0x400ul	//B10 */
#define MASK_DONE 0x800ul	//B11
#define MASK_BLINK 0x1000ul	//B12
#define MASK_BTN_IN 0x2000ul	//B13

struct shift_register {
	uint32_t * reg;
	uint16_t mask_ser;
	uint16_t mask_srclk;
	uint16_t mask_rclk;
	//uint16_t mask_oe;
	//uint16_t mask_srclr;
};

struct shift_register sr_simon = {GPIOB_ODR, 0x100ul, 0x200ul, 0x400ul};

void sr_write(struct shift_register *sr, uint8_t value) {
	for (uint8_t i=0; i<8; ++i) {
		if (value & 0x1) {
			*sr->reg |= sr->mask_ser;
		}
		else {
			*sr->reg &= ~sr->mask_ser;
		}
		*sr->reg |= sr->mask_srclk;
		value >>= 1;
		asm("nop");
		*sr->reg &= ~sr->mask_srclk;
	}
	*sr->reg |= sr->mask_rclk; asm("nop"); asm("nop"); *sr->reg &= ~sr->mask_rclk;
}

uint8_t v = 0x11;
void __isr_systick() {
	*GPIOD_ODR ^= 0x1000;

	v = ((v << 7) | (v >> 1));
	sr_write(&sr_simon, v);

	uint8_t btn_val = (*GPIOB_IDR & MASK_BTN_IN) >> 12;
	if (btn_val) {
		*GPIOB_ODR |= MASK_BLINK;
	}
	else {
		*GPIOB_ODR &= ~MASK_BLINK;
	}
}

void main() {
	*RCC_AHB1ENR |= RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOBEN;

	*NVIC_PRI3 &= 0xff000000ul;
	*NVIC_PRI3 |= 0x0f000000ul;

	*GPIOD_MODER &= 0x3000000ul;
	*GPIOD_MODER |= 0x1000000ul; //D12 (onboard LED) out

	*GPIOB_MODER &= 0xfff0000ul;
	*GPIOB_MODER |= 0x1550000ul; //B8-12 out, B13 in

	*GPIOB_PUPDR &= 0xc000000ul;
	*GPIOB_PUPDR |= 0x8000000ul; //B13 pull-down

	*STK_LOAD = 1000000ul;
	*STK_VAL = 0;
	*STK_CTRL |= (STK_TICKINT | STK_ENABLE);

	while (1) { }
}
