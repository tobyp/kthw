#include <stdint.h>
#include <stddef.h>

#include "stm32f407vg.h"

#include "bomb.h"
#include "simonsays.h"
#include "util.h"
#include "shift_register.h"

#define MASK_B8		0x100ul		//SIMON_SR_SER
#define MASK_B9		0x200ul		//SIMON_SR_SRCLK
#define MASK_B10	0x400ul		//SIMON_SR_RCLK
#define MASK_B13	0x2000ul	//SIMON_BTN_IN

#define MASK_D12	0x1000ul	//D12

struct shift_register sr_simon = {GPIOx_ODR(GPIOB_BASE), MASK_B8, MASK_B9, MASK_B10};
struct simonsays simonsays = {{0, &simonsays_tick, NULL}, 0, 0, 0, {0,0,0,0},6,{0,1,2,3,2,1},&sr_simon, 0, GPIOx_IDR(GPIOB_BASE), MASK_B13};
struct bomb bomb = {0, 0xFFFFFFFF, 0, {NULL, NULL, NULL}, NULL, &simonsays.mod};

void __isr_systick() {
	*GPIOx_ODR(GPIOD_BASE) ^= 0x1000;

	tick(&bomb);
}

void main() {
	/* GPIO */
	*RCC_AHB1ENR |= RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOBEN;

	*GPIOx_MODER(GPIOD_BASE) &= 0x3000000ul;
	*GPIOx_MODER(GPIOD_BASE) |= 0x1000000ul; //D12 (onboard LED) out

	*GPIOx_MODER(GPIOB_BASE) &= 0xfff0000ul;
	*GPIOx_MODER(GPIOB_BASE) |= 0x1550000ul; //B8-12 out, B13 in

	*GPIOx_PUPDR(GPIOB_BASE) &= 0xc000000ul;
	*GPIOx_PUPDR(GPIOB_BASE) |= 0x8000000ul; //B13 pull-down

	/* UART */
	*RCC_AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	*RCC_APB1ENR |= RCC_APB1ENR_USART4EN;

	*GPIOx_MODER(GPIOA_BASE) &= ~0xful;
	*GPIOx_MODER(GPIOA_BASE) |= 0xaul; //PA0 and PA1 Alternate Function

	*GPIOx_AFRL(GPIOA_BASE) &= ~0xfful;
	*GPIOx_AFRL(GPIOA_BASE) |= 0x88ul; //PA0/PA1 to AF8 (UART4 TX/RX)

	*USARTx_BRR(UART4_BASE) |= 1667; //9600 Bd at 16 MHz SYSCLK with OVER8=0
	*USARTx_CR1(UART4_BASE) |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;

	/* SysTick */
	*NVIC_PRIn(3) &= 0xff000000ul;
	*NVIC_PRIn(3) |= 0x0f000000ul;
	*STK_LOAD = 20000ul;
	*STK_VAL = 0;
	*STK_CTRL |= (STK_TICKINT | STK_ENABLE);

	while (1) { }
}
