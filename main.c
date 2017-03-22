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

#define PIN_0	0x0001ul
#define PIN_1	0x0002ul
#define PIN_2	0x0004ul
#define PIN_3	0x0008ul
#define PIN_4	0x0010ul
#define PIN_5	0x0020ul
#define PIN_6	0x0040ul
#define PIN_7	0x0080ul
#define PIN_8	0x0100ul
#define PIN_9	0x0200ul
#define PIN_10	0x0400ul
#define PIN_11	0x0800ul
#define PIN_12	0x1000ul
#define PIN_13	0x2000ul
#define PIN_14	0x4000ul
#define PIN_15	0x8000ul

#define GPIO_OUTB	GPIOx_ODR(GPIOB_BASE)
#define GPIO_INB	GPIOx_IDR(GPIOB_BASE)
#define GPIO_OUTC	GPIOx_ODR(GPIOC_BASE)
#define GPIO_INC	GPIOx_IDR(GPIOC_BASE)
#define GPIO_OUTD	GPIOx_ODR(GPIOD_BASE)
#define GPIO_IND	GPIOx_IDR(GPIOD_BASE)


struct gpio simonsays_ser =	{GPIO_OUTB, PIN_8};
struct gpio sr_srclk =		{GPIO_OUTB, PIN_9};
struct gpio sr_rclk =		{GPIO_OUTB, PIN_10};
struct gpio simonsays_btn =	{GPIO_INB,  PIN_11};
struct gpio morse_led =		{GPIO_OUTB, PIN_12};
struct gpio morse_btn =		{GPIO_INB,  PIN_13};
struct gpio strikes_ser =	{GPIO_OUTB, PIN_14};
struct gpio timer0_ser =	{GPIO_OUTB, PIN_15};

#define morse_adc =			{GPIO_INC,  PIN_0};
#define pwd_adc_pos =		{GPIO_INC,  PIN_1};
struct gpio wires_in0 =		{GPIO_IND,  PIN_8}; //D8
struct gpio wires_in1 =		{GPIO_INC,  PIN_2};
struct gpio wires_in2 =		{GPIO_INC,  PIN_3};
struct gpio wires_in3 =		{GPIO_INC,  PIN_4};
struct gpio wires_in4 =		{GPIO_INC,  PIN_5};
struct gpio wires_in5 =		{GPIO_INC,  PIN_6};
struct gpio cap_in =		{GPIO_INC,  PIN_7};
struct gpio cap0_ser =		{GPIO_OUTC, PIN_8};
struct gpio cap1_ser =		{GPIO_OUTC, PIN_9};
struct gpio mem0_ser =		{GPIO_OUTC, PIN_10};
struct gpio mem1_ser =		{GPIO_OUTC, PIN_11};
struct gpio mem2_ser =		{GPIO_OUTC, PIN_12};
struct gpio mem3_ser =		{GPIO_OUTC, PIN_13};
struct gpio mem_disp_ser =	{GPIO_OUTC, PIN_14};
struct gpio mem_btn_ser =	{GPIO_OUTC, PIN_15};

struct gpio mem_btn_in =	{GPIO_IND,  PIN_0};
struct gpio mem_stage_ser =	{GPIO_OUTD, PIN_1};
struct gpio pwd_lcd_ser =	{GPIO_OUTD, PIN_2};
struct gpio pwd_lcd_rs =	{GPIO_OUTD, PIN_3};
struct gpio pwd_lcd_en =	{GPIO_OUTD, PIN_4};
//D5: STM32F4Discovery: red LED
struct gpio pwd_down_in =	{GPIO_IND,  PIN_6};
struct gpio pwd_submit_in =	{GPIO_IND,  PIN_7};
//D8 wires_in0
struct gpio pwd_up_in =		{GPIO_IND,  PIN_9};
//D12: STM32F4Discovery: green LED
//D13: STM32F4Discovery: orange LED
//D14: STM32F4Discovery: red LED
//D15: STM32F4Discovery: blue LED
//#define SR_OE
//#define SR_SRCLR

uint32_t dummy;
struct gpio DUMMY = {&dummy, 0};


enum {
	SR_TIMER0,	//seconds (ones), use util.h's sevenseg_digits
	SR_TIMER1,	//seconds (tens), use util.h's sevenseg_digits
	SR_TIMER2,	//minutes (ones), use util.h's sevenseg_digits
	SR_TIMER3,	//minutes (tens), use util.h's sevenseg_digits
	SR_STRIKES,	//(MSB) strike 8, ... , strike 1 (LSB)
	SR_FLAGS0,	//(MSB) {<don't care>, <don't care>, BOMB_LBL_FRK, BOMB_PARPORT, BOMB_2BATS, BOMB_SER_EVEN, BOMB_SER_VOW, <don't care>} (LSB)
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
};

struct shreg shregs[] = {
	{&timer0_ser, 0}, //timer0
	{&DUMMY, 0}, //timer1
	{&DUMMY, 0}, //timer2
	{&DUMMY, 0}, //timer3
	{&strikes_ser, 0}, //strikes
	{&DUMMY, 0}, //flags0 (vowel, even, >=2 bats, parallel, FRK)
	{&DUMMY, 0}, //flags1 (5 bits time, 3 bits strikes)

	{&simonsays_ser, 0},

	{&DUMMY, 0}, //morse_freq0
	{&DUMMY, 0}, //morse_freq1
	{&DUMMY, 0}, //morse_freq2
	{&DUMMY, 0}, //morse_freq3

	{&cap0_ser, 0},
	{&cap1_ser, 0},

	{&mem0_ser, 0},
	{&mem1_ser, 0},
	{&mem2_ser, 0},
	{&mem3_ser, 0},
	{&mem_disp_ser, 0},
	{&mem_stage_ser, 0},
	{&mem_btn_ser, 0},

	{&pwd_lcd_ser, 0},
};

enum {
	ADC_MORSE,
	ADC_PWD_POS,
};

struct adc adcs[] = {
	{10, 0},
	{11, 0},
};

struct lcd pwd_lcd = {&pwd_lcd_rs, &pwd_lcd_en, &shregs[SR_PWD_LCD], LCD_NONE, 0};

struct morse morse = {MORSE_MOD_INIT, &morse_led, &morse_btn, &adcs[ADC_MORSE], {&shregs[SR_MORSE_FREQ0], &shregs[SR_MORSE_FREQ1], &shregs[SR_MORSE_FREQ2], &shregs[SR_MORSE_FREQ3]}};
struct simonsays simonsays = {SIMONSAYS_MOD_INIT, &simonsays_btn, &shregs[SR_SIMON_SAYS]};
struct wires wires = {WIRES_MOD_INIT, {&wires_in0, &wires_in1, &wires_in2, &wires_in3, &wires_in4, &wires_in5}};
struct capacitor capacitor = {CAPACITOR_MOD_INIT, &cap_in, {&shregs[SR_CAP0], &shregs[SR_CAP1]}};
struct memory memory = {MEMORY_MOD_INIT, &mem_btn_in, &shregs[SR_MEM_BTN], &shregs[SR_MEM_STAGE], &shregs[SR_MEM_DISP], {&shregs[SR_MEM0], &shregs[SR_MEM1], &shregs[SR_MEM2], &shregs[SR_MEM3]}};
struct password password = {PASSWORD_MOD_INIT, &pwd_submit_in, {&pwd_up_in, &pwd_down_in}, &adcs[ADC_PWD_POS], &pwd_lcd};

struct bomb bomb = {{&DUMMY, &DUMMY}, {&shregs[SR_FLAGS0], &shregs[SR_FLAGS1]}, &shregs[SR_STRIKES], {&shregs[SR_TIMER0], &shregs[SR_TIMER1], &shregs[SR_TIMER2], &shregs[SR_TIMER3]}};

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
	*RCC_AHB1ENR |= RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIODEN;

	*GPIOx_MODER(GPIOB_BASE) &= ~0xffff0000ul;
	*GPIOx_MODER(GPIOB_BASE) |=  0x51150000ul; //B8-10,12,14-15 out, B11,13 in
	*GPIOx_PUPDR(GPIOB_BASE) &= ~0x0cc00000ul;
	*GPIOx_PUPDR(GPIOB_BASE) |=  0x08800000ul; //B11,13 pull-down

	*GPIOx_MODER(GPIOC_BASE) &= ~0xfffffff0ul;
	*GPIOx_MODER(GPIOC_BASE) |=  0x55550000ul; //C2-7 in, C8-15 out
	*GPIOx_PUPDR(GPIOC_BASE) &= ~0x0000fff0ul;
	*GPIOx_PUPDR(GPIOC_BASE) |=  0x0000aaa0ul; //C2-7 pull-down

	*GPIOx_MODER(GPIOD_BASE) &= ~0x0303f3fful;
	*GPIOx_MODER(GPIOD_BASE) |=  0x01000154ul; //D0,6-9 in, D1-4 out, D12 (onboard LED) out
	*GPIOx_PUPDR(GPIOD_BASE) &= ~0x000ff003ul;
	*GPIOx_PUPDR(GPIOD_BASE) |=  0x000aa002ul; //D0,6-9 pull-down

	/* ADC */
	*RCC_AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	*GPIOx_MODER(GPIOC_BASE) &= ~0xful;
	*GPIOx_MODER(GPIOC_BASE) |= 0xful; //C0-1 analog

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
	bomb_add_module(&bomb, &simonsays.module);
	bomb_add_module(&bomb, &morse.module);
	bomb_add_module(&bomb, &wires.module);
	bomb_add_module(&bomb, &capacitor.module);
	bomb_add_module(&bomb, &memory.module);
	bomb_add_module(&bomb, &password.module);

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
			if (shregs[j].value_cache & 0x1) *shregs[j].ser->reg |= shregs[j].ser->mask;
			else *shregs[j].ser->reg &= ~shregs[j].ser->mask;
			shregs[j].value_cache >>= 1;
		}
		*sr_srclk.reg |= sr_srclk.mask; *sr_srclk.reg &= ~sr_srclk.mask;
	}
	*sr_rclk.reg |= sr_rclk.mask; *sr_rclk.reg &= ~sr_rclk.mask;
	//lcd (part 2)
	if (pwd_lcd.mode < LCD_NONE) {
		*pwd_lcd.lcd_en->reg |=  pwd_lcd.lcd_en->mask;
		if (pwd_lcd.mode) *pwd_lcd.lcd_rs->reg |= pwd_lcd.lcd_rs->mask;
		else *pwd_lcd.lcd_rs->reg &= ~pwd_lcd.lcd_rs->mask;

		delay(1);

		*pwd_lcd.lcd_en->reg &= ~pwd_lcd.lcd_en->mask;
		pwd_lcd.mode = LCD_NONE;
	}

	current_adc = (current_adc + 1) % (sizeof(adcs)/sizeof(struct adc));
	*ADCx_SQR3(ADC1_BASE) &= ~0x1f;
	*ADCx_SQR3(ADC1_BASE) |= adcs[current_adc].channel;
	*ADCx_CR2(ADC1_BASE) |= ADC_CR2_SWSTART;
}