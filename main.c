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

#include <stdint.h>

#include "stm32f407vg.h"

#include "util.h"
#include "bomb.h"
#include "simonsays.h"
#include "morse.h"
#include "wires.h"
#include "capacitor.h"
#include "memory.h"
#include "password.h"

#include "pins.inc.h"

struct morse morse = {MORSE_MOD_INIT, &pins[GP_MORSE_LED], &pins[GP_MORSE_BTN], &adcs[ADC_MORSE], {&shregs[SR_MORSE_FREQ0], &shregs[SR_MORSE_FREQ1], &shregs[SR_MORSE_FREQ2], &shregs[SR_MORSE_FREQ3]}};
struct simonsays simonsays = {SIMONSAYS_MOD_INIT, &pins[GP_SIMONSAYS_BTN], &shregs[SR_SIMON_SAYS]};
struct wires wires = {WIRES_MOD_INIT, &shregs[SR_WIRES], &adcs[ADC_WIRES]};
struct capacitor capacitor = {CAPACITOR_MOD_INIT, &pins[GP_CAP_IN], {&shregs[SR_CAP0], &shregs[SR_CAP1]}};
struct memory memory = {MEMORY_MOD_INIT, &pins[GP_MEM_BTN_IN], &shregs[SR_MEM_BTN], &shregs[SR_MEM_STAGE], &shregs[SR_MEM_DISP], {&shregs[SR_MEM0], &shregs[SR_MEM1], &shregs[SR_MEM2], &shregs[SR_MEM3]}};
struct password password = {PASSWORD_MOD_INIT, &pins[GP_PWD_IN], &shregs[SR_PWD_SER], &lcds[LCD_PWD]};

struct bomb bomb = {{&pins[GP_FLAGS0_IN], &pins[GP_FLAGS1_IN]}, {&shregs[SR_FLAGS0], &shregs[SR_FLAGS1]}, &shregs[SR_STRIKE_COMPLETE], {&shregs[SR_TIMER0], &shregs[SR_TIMER1], &shregs[SR_TIMER2], &shregs[SR_TIMER3]}, &pins[GP_BUZZER], &pins[GP_BUZZER2], &pins[GP_CAP_IN]};

int main() {
	/* RCC/PLL */
	//f_{VCO} = f_{PLL IN} * \frac{N}{M}; 50 <= N <= 432; 2 <= M <= 63
	//N := 63
	//M := 12
	*RCC_PLLCFGR &= ~0x00007ffful;
	*RCC_PLLCFGR |=  0x00002fc0ul | 0x0000000cul;
	//f_{VCO} = 16 MHz * 21 / 4 = 84 MHz

	//f_{OTG_SDIO_RNG} = f_{VCO} / Q; 2 <= Q <= 15
	//Q := 2
	*RCC_PLLCFGR &= ~0x0f000000ul;
	*RCC_PLLCFGR |=  0x02000000ul;
	//f_{OTG_SDIO_RNG} = 84 MHz / 2 = 42 MHz

	*RCC_CR |= RCC_CR_PLLON;
	while ((*RCC_CR & RCC_CR_PLLRDY) == 0) { }

	/* GPIO */
	*RCC_AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN | RCC_AHB1ENR_GPIOHEN;

	for (uint32_t i=0; i<sizeof(pins)/(sizeof(struct gpio)); ++i) {
		struct gpio * p = &pins[i];
		uint32_t mode_mask = GM_MASK << (p->pin << 1);
		uint32_t mode = p->mode << (p->pin << 1);
		*GPIOx_MODER(p->base) &= ~mode_mask;
		*GPIOx_MODER(p->base) |= mode;
		if (p->mode == GM_IN) {
			*GPIOx_PUPDR(p->base) &= ~mode_mask;
			uint32_t pupd = GPP_DOWN << (p->pin << 1);
			*GPIOx_PUPDR(p->base) |= pupd;
		}
	}

	/* ADC */
	*RCC_AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	*GPIOx_MODER(GPIOC_BASE) &= ~0xful;
	*GPIOx_MODER(GPIOC_BASE) |=  0xful; //C0-1 analog

	*RCC_APB2ENR |= RCC_APB2ENR_ADC1EN;

	*ADCx_CR1(ADC1_BASE) |= ADC_CR1_EOCIE;
	*ADCx_CR2(ADC1_BASE) |= ADC_CR2_ADON;

	*ADCx_SMPR1(ADC1_BASE) |= 0x07ffffff;
	*ADCx_SMPR2(ADC1_BASE) |= 0x3fffffff; //sample all channels at 480 cycles
	*ADCx_SQR3(ADC1_BASE) |= adcs[0].channel;

	*NVIC_ISER(0) |= (1 << 18);

	*ADCx_CR2(ADC1_BASE) |= ADC_CR2_SWSTART;

	/* RNG */
	*RCC_AHB2ENR |= RCC_AHB2ENR_RNGEN;
	*RNG_CR |= RNG_CR_RNGEN;

	/* UART */
	*RCC_AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	*RCC_APB1ENR |= RCC_APB1ENR_USART4EN;

	*GPIOx_MODER(GPIOA_BASE) &= ~0xful;
	*GPIOx_MODER(GPIOA_BASE) |= 0xaul; //PA0 and PA1 Alternate Function

	*GPIOx_AFRL(GPIOA_BASE) &= ~0xfful;
	*GPIOx_AFRL(GPIOA_BASE) |= 0x88ul; //PA0 and PA1 to AF8 (UART4 TX/RX)

	*USARTx_BRR(UART4_BASE) |= 139; //139 is 115200 Bd, 1667 is 9600 Bd at 16 MHz SYSCLK with OVER8=0
	*USARTx_CR1(UART4_BASE) |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
	uart_enabled = 1;

	/* LCD power up */
	delay(150);

	/* Bomb */
	bomb_add_module(&bomb, &capacitor.module);
	bomb_add_module(&bomb, &password.module);
	bomb_add_module(&bomb, &memory.module);
	bomb_add_module(&bomb, &wires.module);
	bomb_add_module(&bomb, &morse.module);
	bomb_add_module(&bomb, &simonsays.module);

	/* System Tick Timer */
	*NVIC_PRIn(3) &= 0xff000000ul;
	*NVIC_PRIn(3) |= 0x0f000000ul;
	*STK_LOAD = 2000000ul / TICKS_PER_SEC;
	*STK_VAL = 0;
	*STK_CTRL |= (STK_TICKINT | STK_ENABLE);

	/* And now, we wait. */
	while(1) { }

	return 0;
}

uint8_t current_adc = 0;

void __isr_adc() {
	adcs[current_adc].value = *ADCx_DR(ADC1_BASE);
}

void __isr_systick() {
	//*GPIOx_ODR(GPIOD_BASE) ^= 0x1000;  //D12, green LED on the discovery board
	tick(&bomb);
	/* LCDs (part 1) */
	for (uint8_t i=0; i<(sizeof(lcds)/sizeof(struct lcd)); ++i) {
		lcds[i].lcd_data->value = lcds[i].cmd;
	}
	/* Shift Registers. We shift all registers in parallel, eight times per systick. */
	for (uint8_t i=0; i<(sizeof(shregs)/sizeof(struct shreg)); ++i) {
		shregs[i].value_cache = shregs[i].value;
	}
	for (uint8_t i=0; i<8; ++i) {
		for (uint8_t j=0; j<(sizeof(shregs)/sizeof(struct shreg)); ++j) {
			gpio_set(shregs[j].ser, shregs[j].value_cache & 0x1);
			shregs[j].value_cache >>= 1;
		}
		gpio_set(&pins[GP_SR_SRCLK], 1); gpio_set(&pins[GP_SR_SRCLK], 0);
	}
	gpio_set(&pins[GP_SR_RCLK], 1); gpio_set(&pins[GP_SR_RCLK], 0);
	/* LCDs (part 2) */
	for (uint8_t i=0; i<(sizeof(lcds)/sizeof(struct lcd)); ++i) {
		if (lcds[i].mode < LCD_NONE) {
			gpio_set(lcds[i].lcd_en, 1);
			if (lcds[i].mode) gpio_set(lcds[i].lcd_rs, 1);
			else gpio_set(lcds[i].lcd_rs, 0);

			delay(1);

			gpio_set(lcds[i].lcd_en, 0);
			lcds[i].mode = LCD_NONE;
		}
	}
	/* ADCs */
	current_adc = (current_adc + 1) % (sizeof(adcs)/sizeof(struct adc));
	*ADCx_SQR3(ADC1_BASE) &= ~0x1f;
	*ADCx_SQR3(ADC1_BASE) |= adcs[current_adc].channel;
	*ADCx_CR2(ADC1_BASE) |= ADC_CR2_SWSTART;
}
