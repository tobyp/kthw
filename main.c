#include <stdint.h>
#include <stddef.h>

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

enum {
	SR_TIMER0,	//seconds (ones), use util.h's sevenseg_digits
	SR_TIMER1,	//seconds (tens), use util.h's sevenseg_digits
	SR_TIMER2,	//minutes (ones), use util.h's sevenseg_digits
	SR_TIMER3,	//minutes (tens), use util.h's sevenseg_digits
	SR_STRIKE_COMPLETE,	//(MSB) complete 5..1, strike 3..1 (LSB)
	SR_FLAGS0,	//(MSB) {<don't care>, <don't care>, FL_LBL_FRK, FL_PARPORT, FL_2BATS, FL_SER_EVEN, FL_SER_VOW, <don't care>} (LSB)
	SR_FLAGS1,	//(MSB) 5 bits = time / 30s; 2 bits = strike limit

	SR_SIMON_SAYS,	// (MSB) {Buttons (GRYB), LEDs (GRYB)} (LSB)

	SR_MORSE_FREQ0,
	SR_MORSE_FREQ1,
	SR_MORSE_FREQ2,
	SR_MORSE_FREQ3,

	SR_CAP0,
	SR_CAP1,

	SR_MEM0,
	SR_MEM1,
	SR_MEM2,
	SR_MEM3,
	SR_MEM_DISP,
	SR_MEM_STAGE,
	SR_MEM_BTN,

	SR_PWD_LCD,
	SR_PWD_SER,

	SR_WIRES,
};

struct shreg shregs[] = {
	{&pins[GP_TIMER0_SER], 0}, //timer0
	{&pins[GP_TIMER1_SER], 0}, //timer1
	{&pins[GP_TIMER2_SER], 0}, //timer2
	{&pins[GP_TIMER3_SER], 0}, //timer3
	{&pins[GP_STRIKES_SER], 0}, //strikes
	{&pins[GP_FLAGS0_SER], 0}, //flags0 (vowel, even, >=2 bats, parallel, FRK)
	{&pins[GP_FLAGS1_SER], 0}, //flags1 (5 bits time, 3 bits strikes)

	{&pins[GP_SIMONSAYS_SER], 0},

	{&pins[GP_MORSE_FREQ0_SER], 0}, //morse_freq0
	{&pins[GP_MORSE_FREQ1_SER], 0}, //morse_freq1
	{&pins[GP_MORSE_FREQ2_SER], 0}, //morse_freq2
	{&pins[GP_MORSE_FREQ3_SER], 0}, //morse_freq3

	{&pins[GP_CAP0_SER], 0},
	{&pins[GP_CAP1_SER], 0},

	{&pins[GP_MEM0_SER], 0},
	{&pins[GP_MEM1_SER], 0},
	{&pins[GP_MEM2_SER], 0},
	{&pins[GP_MEM3_SER], 0},
	{&pins[GP_MEM_DISP_SER], 0},
	{&pins[GP_MEM_STAGE_SER], 0},
	{&pins[GP_MEM_BTN_SER], 0},

	{&pins[GP_PWD_LCD_SER], 0},
	{&pins[GP_PWD_SER], 0},

	{&pins[GP_WIRES_SER], 0},
};

enum {
	ADC_MORSE,
};

struct adc adcs[] = {
	{10, 0},
};

struct lcd pwd_lcd = {&pins[GP_PWD_LCD_RS], &pins[GP_PWD_LCD_EN], &shregs[SR_PWD_LCD], LCD_NONE, 0};

struct morse morse = {MORSE_MOD_INIT, &pins[GP_MORSE_LED], &pins[GP_MORSE_BTN], &adcs[ADC_MORSE], {&shregs[SR_MORSE_FREQ0], &shregs[SR_MORSE_FREQ1], &shregs[SR_MORSE_FREQ2], &shregs[SR_MORSE_FREQ3]}};
struct simonsays simonsays = {SIMONSAYS_MOD_INIT, &pins[GP_SIMONSAYS_BTN], &shregs[SR_SIMON_SAYS]};
struct wires wires = {WIRES_MOD_INIT, &shregs[SR_WIRES], &pins[GP_WIRES_IN]};
struct capacitor capacitor = {CAPACITOR_MOD_INIT, &pins[GP_CAP_IN], {&shregs[SR_CAP0], &shregs[SR_CAP1]}};
struct memory memory = {MEMORY_MOD_INIT, &pins[GP_MEM_BTN_IN], &shregs[SR_MEM_BTN], &shregs[SR_MEM_STAGE], &shregs[SR_MEM_DISP], {&shregs[SR_MEM0], &shregs[SR_MEM1], &shregs[SR_MEM2], &shregs[SR_MEM3]}};
struct password password = {PASSWORD_MOD_INIT, &pins[GP_PWD_IN], &shregs[SR_PWD_SER], &pwd_lcd};

struct bomb bomb = {{&pins[GP_FLAGS0_IN], &pins[GP_FLAGS1_IN]}, {&shregs[SR_FLAGS0], &shregs[SR_FLAGS1]}, &shregs[SR_STRIKE_COMPLETE], {&shregs[SR_TIMER0], &shregs[SR_TIMER1], &shregs[SR_TIMER2], &shregs[SR_TIMER3]}, &pins[GP_BUZZER]};

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

	//activate PLL
	*RCC_CR |= RCC_CR_PLLON;
	//wait PLLRDY
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
	//*ADCx_CR1(ADC1_BASE) |= ADC_CR1_SCAN;

	*ADCx_CR2(ADC1_BASE) |= ADC_CR2_ADON;
	//*ADCx_CR2(ADC1_BASE) |= ADC_CR2_CONT;
	//*ADCx_CR2(ADC1_BASE) |= ADC_CR2_EOCS;

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

	/* LCD power up */
	delay(150);

	/* BOMB */
	bomb_add_module(&bomb, &capacitor.module);
	bomb_add_module(&bomb, &password.module);
	bomb_add_module(&bomb, &memory.module);
	bomb_add_module(&bomb, &wires.module);
	bomb_add_module(&bomb, &morse.module);
	bomb_add_module(&bomb, &simonsays.module);

	/* SysTick */
	*NVIC_PRIn(3) &= 0xff000000ul;
	*NVIC_PRIn(3) |= 0x0f000000ul;
	*STK_LOAD = 20000ul;
	*STK_VAL = 0;
	*STK_CTRL |= (STK_TICKINT | STK_ENABLE);

	while(1) { }

	return 0;
}

uint8_t current_adc = 0;

void __isr_adc() {
	adcs[current_adc].value = *ADCx_DR(ADC1_BASE);
}

void __isr_systick() {
	//*GPIOx_ODR(GPIOD_BASE) ^= 0x1000;
	tick(&bomb);
	//lcd (part 1)
	shregs[SR_PWD_LCD].value = pwd_lcd.cmd;
	//commit shift registers
	for (uint8_t j=0; j<(sizeof(shregs)/sizeof(struct shreg)); ++j) {
		shregs[j].value_cache = shregs[j].value;
	}
	for (uint8_t i=0; i<8; ++i) {
		for (uint8_t j=0; j<(sizeof(shregs)/sizeof(struct shreg)); ++j) {
			gpio_set(shregs[j].ser, shregs[j].value_cache & 0x1);
			shregs[j].value_cache >>= 1;
		}
		gpio_set(&pins[GP_SR_SRCLK], 1); gpio_set(&pins[GP_SR_SRCLK], 0);
	}
	gpio_set(&pins[GP_SR_RCLK], 1); gpio_set(&pins[GP_SR_RCLK], 0);
	//lcd (part 2)
	if (pwd_lcd.mode < LCD_NONE) {
		gpio_set(pwd_lcd.lcd_en, 1);
		if (pwd_lcd.mode) gpio_set(pwd_lcd.lcd_rs, 1);
		else gpio_set(pwd_lcd.lcd_rs, 0);

		delay(1);

		gpio_set(pwd_lcd.lcd_en, 0);
		pwd_lcd.mode = LCD_NONE;
	}

	current_adc = (current_adc + 1) % (sizeof(adcs)/sizeof(struct adc));
	*ADCx_SQR3(ADC1_BASE) &= ~0x1f;
	*ADCx_SQR3(ADC1_BASE) |= adcs[current_adc].channel;
	*ADCx_CR2(ADC1_BASE) |= ADC_CR2_SWSTART;
}