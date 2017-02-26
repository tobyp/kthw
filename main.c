#include <stdint.h>
#include <stddef.h>

#include "stm32f407vg.h"

#include "util.h"
#include "bomb.h"
#include "simonsays.h"
#include "morse.h"
#include "wires.h"
#include "capacitor.h"

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


struct gpio simonsays_ser =	{GPIO_OUTB, PIN_8};
struct gpio sr_srclk =		{GPIO_OUTB, PIN_9};
struct gpio sr_rclk =		{GPIO_OUTB, PIN_10};
struct gpio simonsays_btn =	{GPIO_INB,  PIN_11};
struct gpio morse_led =		{GPIO_OUTB, PIN_12};
struct gpio morse_btn =		{GPIO_INB,  PIN_13};
struct gpio strikes_ser =	{GPIO_OUTB, PIN_14};
struct gpio timer0_ser =	{GPIO_OUTB, PIN_15};

#define morse_adc =			{GPIO_INC,  PIN_0};
struct gpio wires_in0 =		{GPIO_INC,  PIN_1};
struct gpio wires_in1 =		{GPIO_INC,  PIN_2};
struct gpio wires_in2 =		{GPIO_INC,  PIN_3};
struct gpio wires_in3 =		{GPIO_INC,  PIN_4};
struct gpio wires_in4 =		{GPIO_INC,  PIN_5};
struct gpio wires_in5 =		{GPIO_INC,  PIN_6};
struct gpio cap_in =		{GPIO_INC,  PIN_7};
struct gpio cap0_ser =		{GPIO_OUTC, PIN_8};
struct gpio cap1_ser =		{GPIO_OUTC, PIN_9};

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
};

enum {
	ADC_MORSE,
};

struct adc adcs[] = {
	{10, 0}, //morse
};

struct morse morse = {MORSE_MOD_INIT, &morse_led, &morse_btn, &adcs[ADC_MORSE], {&shregs[SR_MORSE_FREQ0], &shregs[SR_MORSE_FREQ1], &shregs[SR_MORSE_FREQ2], &shregs[SR_MORSE_FREQ3]}};
struct simonsays simonsays = {SIMONSAYS_MOD_INIT, &simonsays_btn, &shregs[SR_SIMON_SAYS]};
struct wires wires = {WIRES_MOD_INIT, {&wires_in0, &wires_in1, &wires_in2, &wires_in3, &wires_in4, &wires_in5}};
struct capacitor capacitor = {CAPACITOR_MOD_INIT, &cap_in, {&shregs[SR_CAP0], &shregs[SR_CAP1]}};
struct bomb bomb = {{&DUMMY, &DUMMY}, {&shregs[SR_FLAGS0], &shregs[SR_FLAGS1]}, &shregs[SR_STRIKES], {&shregs[SR_TIMER0], &shregs[SR_TIMER1], &shregs[SR_TIMER2], &shregs[SR_TIMER3]}};

void main() {
	/* GPIO */
	*RCC_AHB1ENR |= RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN;

	*GPIOx_MODER(GPIOB_BASE) &= ~0xffff0000ul;
	*GPIOx_MODER(GPIOB_BASE) |=  0x51150000ul; //B8-10,12,14-15 out, B11,13 in

	*GPIOx_PUPDR(GPIOB_BASE) &= ~0x0cc00000ul;
	*GPIOx_PUPDR(GPIOB_BASE) |=  0x08800000ul; //B11,13 pull-down

	*GPIOx_MODER(GPIOC_BASE) &= ~0x000ffffcul;
	*GPIOx_MODER(GPIOC_BASE) |=  0x00050000ul; //C1-7 in, C8-9 out

	*GPIOx_PUPDR(GPIOC_BASE) &= ~0x0000fffcul;
	*GPIOx_PUPDR(GPIOC_BASE) |=  0x0000aaa8ul; //C1-7 pull-down

	*GPIOx_MODER(GPIOD_BASE) &= ~0x03000000ul;
	*GPIOx_MODER(GPIOD_BASE) |=  0x01000000ul; //D12 (onboard LED) out

	/* UART */
	*RCC_AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	*RCC_APB1ENR |= RCC_APB1ENR_USART4EN;

	*GPIOx_MODER(GPIOA_BASE) &= ~0xful;
	*GPIOx_MODER(GPIOA_BASE) |= 0xaul; //PA0 and PA1 Alternate Function

	*GPIOx_AFRL(GPIOA_BASE) &= ~0xfful;
	*GPIOx_AFRL(GPIOA_BASE) |= 0x88ul; //PA0 and PA1 to AF8 (UART4 TX/RX)

	*USARTx_BRR(UART4_BASE) |= 139; //139 is 115200 Bd, 1667 is 9600 Bd at 16 MHz SYSCLK with OVER8=0
	*USARTx_CR1(UART4_BASE) |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;

	/* ADC */
	*RCC_AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	*GPIOx_MODER(GPIOC_BASE) &= ~0x3ul;
	*GPIOx_MODER(GPIOC_BASE) |= 0x3ul; //C0 analog

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

	/* BOMB */
	bomb_add_module(&bomb, &simonsays.module);
	bomb_add_module(&bomb, &morse.module);
	bomb_add_module(&bomb, &wires.module);
	bomb_add_module(&bomb, &capacitor.module);

	/* SysTick */
	*NVIC_PRIn(3) &= 0xff000000ul;
	*NVIC_PRIn(3) |= 0x0f000000ul;
	*STK_LOAD = 20000ul;
	*STK_VAL = 0;
	*STK_CTRL |= (STK_TICKINT | STK_ENABLE);

	while(1) { }
}

uint8_t current_adc = 0;

void __isr_adc() {
	adcs[current_adc].value = *ADCx_DR(ADC1_BASE);
	current_adc = (current_adc + 1) % (sizeof(adcs)/sizeof(struct adc));
	if (current_adc != 0) {
		*ADCx_SQR3(ADC1_BASE) |= adcs[current_adc].channel;
		*ADCx_CR2(ADC1_BASE) |= ADC_CR2_SWSTART;
	}
}

void __isr_systick() {
	//*GPIOx_ODR(GPIOD_BASE) ^= 0x1000;
	tick(&bomb);
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
	//print("adc: "); print_uint(adcs[0].value); print("\n");
	if (current_adc != 0) {
		print("interrupted adc sequence... ??? good luck.\n");
	}
	current_adc = 0;
	*ADCx_CR2(ADC1_BASE) |= ADC_CR2_SWSTART;
}