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

static const uint32_t dummy_gpio_port[10] = {0};
#define DUMMY_BASE ((uint32_t)&dummy_gpio_port)

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
	GP_WIRES_IN,
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

//struct gpio morse_adc =		{GPIOC_BASE, GM_IN,  PIN_0};
//struct gpio _adc =			{GPIOC_BASE, GM_IN,  PIN_1};

struct gpio pins[] = {
	{GPIOC_BASE, GM_OUT, PIN_3}, //GP_SR_SRCLK
	{GPIOC_BASE, GM_OUT, PIN_2}, //GP_SR_RCLK

	{GPIOA_BASE, GM_OUT, PIN_3}, //GP_TIMER0_SER
	{GPIOA_BASE, GM_OUT, PIN_5}, //GP_TIMER1_SER
	{GPIOA_BASE, GM_OUT, PIN_7}, //GP_TIMER2_SER
	{GPIOC_BASE, GM_OUT, PIN_5}, //GP_TIMER3_SER
	{GPIOB_BASE, GM_OUT, PIN_1}, //GP_BUZZER
	{GPIOB_BASE, GM_OUT, PIN_15},//{GPIOB_BASE, GM_OUT, PIN_1}, //GP_BUZZER2
	{GPIOB_BASE, GM_OUT, PIN_12}, //GP_FLAGS0_SER
	{GPIOB_BASE, GM_OUT, PIN_14}, //GP_FLAGS1_SER
	{GPIOD_BASE, GM_IN,  PIN_8}, //GP_FLAGS0_IN
	{GPIOD_BASE, GM_IN,  PIN_10}, //GP_FLAGS1_IN
	{GPIOB_BASE, GM_OUT, PIN_0}, //GP_STRIKES_SER

	{GPIOD_BASE, GM_OUT, PIN_11}, //GP_SIMONSAYS_SER
	{GPIOE_BASE, GM_IN,  PIN_8}, //GP_SIMONSAYS_BTN

	{GPIOE_BASE, GM_OUT, PIN_9}, //GP_MORSE_FREQ0_SER
	{GPIOE_BASE, GM_OUT, PIN_11}, //GP_MORSE_FREQ1_SER
	{GPIOE_BASE, GM_OUT, PIN_13}, //GP_MORSE_FREQ2_SER
	{GPIOE_BASE, GM_OUT, PIN_15}, //GP_MORSE_FREQ3_SER
	{GPIOE_BASE, GM_OUT, PIN_10}, //GP_MORSE_LED
	{GPIOE_BASE, GM_IN,  PIN_12}, //GP_MORSE_BTN

	{GPIOE_BASE, GM_OUT, PIN_14}, //GP_WIRES_SER
	{GPIOB_BASE, GM_IN,  PIN_10}, //GP_WIRES_IN

	{GPIOE_BASE, GM_OUT, PIN_2}, //GP_CAP0_SER
	{GPIOC_BASE, GM_OUT, PIN_7}, //GP_CAP1_SER
	{GPIOE_BASE, GM_IN,  PIN_3}, //GP_CAP_IN

	{GPIOE_BASE, GM_OUT, PIN_4}, //GP_MEM0_SER
	{GPIOE_BASE, GM_OUT, PIN_6}, //GP_MEM1_SER
	{GPIOC_BASE, GM_OUT, PIN_14}, //GP_MEM2_SER
	{GPIOB_BASE, GM_OUT, PIN_8}, //GP_MEM3_SER
	{GPIOB_BASE, GM_OUT, PIN_9}, //GP_MEM_DISP_SER
	{GPIOC_BASE, GM_OUT, PIN_15}, //GP_MEM_STAGE_SER
	{GPIOC_BASE, GM_OUT, PIN_13}, //GP_MEM_BTN_SER
	{GPIOE_BASE, GM_IN,  PIN_5}, //GP_MEM_BTN_IN

	{GPIOD_BASE, GM_OUT, PIN_3}, //GP_PWD_SER
	{GPIOC_BASE, GM_IN,  PIN_12}, //GP_PWD_IN
	{GPIOD_BASE, GM_OUT, PIN_4}, //GP_PWD_LCD_SER
	{GPIOD_BASE, GM_OUT, PIN_2}, //GP_PWD_LCD_RS
	{GPIOD_BASE, GM_OUT, PIN_0}, //GP_PWD_LCD_EN
};

//pins conected/AF on reset
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
