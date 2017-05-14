#define PIN_0	0
#define PIN_1	1
#define PIN_2	2
#define PIN_3	3
#define PIN_4	4
#define PIN_5	5
#define PIN_6	6
#define PIN_7	7
#define PIN_8	8
#define PIN_9	9
#define PIN_10	10
#define PIN_11	11
#define PIN_12	12
#define PIN_13	13
#define PIN_14	14
#define PIN_15	15

#define GM_MASK		0x3
#define GM_OUT		0x1
#define GM_IN		0x0
#define GPP_DOWN	0x2

#define GPIO_OUT(bank, idx) {GPIO##bank##_BASE, GM_OUT, PIN_##idx}
#define GPIO_IN(bank, idx) {GPIO##bank##_BASE, GM_IN, PIN_##idx}

/*
//Useful if you temporarily want to disable a pin - just uncomment and use the DUMMY bank
static const uint32_t dummy_gpio_port[10] = {0};
#define GPIODUMMY_BASE ((uint32_t)&dummy_gpio_port)
*/

enum {
	GP_SR_SRCLK,
	GP_SR_RCLK,
	GP_TIMER0_SER,
	GP_TIMER1_SER,
	GP_TIMER2_SER,
	GP_TIMER3_SER,
	GP_BUZZER,
	GP_BUZZER2,
	GP_FLAGS0_SER,
	GP_FLAGS1_SER,
	GP_FLAGS0_IN,
	GP_FLAGS1_IN,
	GP_STRIKES_SER,
	GP_SIMONSAYS_SER,
	GP_SIMONSAYS_BTN,
	GP_MORSE_FREQ0_SER,
	GP_MORSE_FREQ1_SER,
	GP_MORSE_FREQ2_SER,
	GP_MORSE_FREQ3_SER,
	GP_MORSE_LED,
	GP_MORSE_BTN,
	GP_WIRES_SER,
	GP_CAP0_SER,
	GP_CAP1_SER,
	GP_CAP_IN,
	GP_MEM0_SER,
	GP_MEM1_SER,
	GP_MEM2_SER,
	GP_MEM3_SER,
	GP_MEM_DISP_SER,
	GP_MEM_STAGE_SER,
	GP_MEM_BTN_SER,
	GP_MEM_BTN_IN,
	GP_PWD_SER,
	GP_PWD_IN,
	GP_PWD_LCD_SER,
	GP_PWD_LCD_RS,
	GP_PWD_LCD_EN,
};

struct gpio pins[] = {
	GPIO_OUT(C, 3), //GP_SR_SRCLK
	GPIO_OUT(C, 2), //GP_SR_RCLK

	GPIO_OUT(A, 3), //GP_TIMER0_SER
	GPIO_OUT(A, 5), //GP_TIMER1_SER
	GPIO_OUT(A, 7), //GP_TIMER2_SER
	GPIO_OUT(C, 5), //GP_TIMER3_SER
	GPIO_OUT(B, 1), //GP_BUZZER
	GPIO_OUT(B, 15), //GP_BUZZER2
	GPIO_OUT(B, 12), //GP_FLAGS0_SER
	GPIO_OUT(B, 14), //GP_FLAGS1_SER
	GPIO_IN(D, 8), //GP_FLAGS0_IN
	GPIO_IN(D, 10), //GP_FLAGS1_IN
	GPIO_OUT(B, 0), //GP_STRIKES_SER

	GPIO_OUT(D, 11), //GP_SIMONSAYS_SER
	GPIO_IN(E, 8), //GP_SIMONSAYS_BTN

	GPIO_OUT(E, 9), //GP_MORSE_FREQ0_SER
	GPIO_OUT(E, 11), //GP_MORSE_FREQ1_SER
	GPIO_OUT(E, 13), //GP_MORSE_FREQ2_SER
	GPIO_OUT(E, 15), //GP_MORSE_FREQ3_SER
	GPIO_OUT(E, 10), //GP_MORSE_LED
	GPIO_IN(E, 12), //GP_MORSE_BTN

	GPIO_OUT(E, 14), //GP_WIRES_SER

	GPIO_OUT(E, 2), //GP_CAP0_SER
	GPIO_OUT(C, 7), //GP_CAP1_SER
	GPIO_IN(E, 3), //GP_CAP_IN

	GPIO_OUT(E, 4), //GP_MEM0_SER
	GPIO_OUT(E, 6), //GP_MEM1_SER
	GPIO_OUT(C, 14), //GP_MEM2_SER
	GPIO_OUT(B, 8), //GP_MEM3_SER
	GPIO_OUT(B, 9), //GP_MEM_DISP_SER
	GPIO_OUT(C, 15), //GP_MEM_STAGE_SER
	GPIO_OUT(C, 13), //GP_MEM_BTN_SER
	GPIO_IN(E, 5), //GP_MEM_BTN_IN

	GPIO_OUT(D, 3), //GP_PWD_SER
	GPIO_IN(C, 12), //GP_PWD_IN
	GPIO_OUT(D, 4), //GP_PWD_LCD_SER
	GPIO_OUT(D, 2), //GP_PWD_LCD_RS
	GPIO_OUT(D, 0), //GP_PWD_LCD_EN
};

//pins conected/initialized to AF on reset
//A13: JTMS
//A14: JLCK
//A15: JTDI
//B3: JLDO
//B4: NJTRST
//D5: STM32F4Discovery: red LED
//D12: STM32F4Discovery: green LED
//D13: STM32F4Discovery: orange LED
//D14: STM32F4Discovery: red LED
//D15: STM32F4Discovery: blue LED

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

/* ADCS */
/* To add more ADCs, make sure to adapt the port settings in the ADC section of main() */
enum {
	ADC_MORSE,
	ADC_WIRES,
};

struct adc adcs[] = {
	{10, 0},
	{11, 0},
};
