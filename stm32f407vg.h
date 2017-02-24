/* CORTEX-M FEATURES */
/* Nested Vector Interrupt Controller */
#define NVIC_BASE	0xe000e100ul

#define NVIC_PRIn(n) ((uint32_t*)(NVIC_BASE+0x300+4*(n)))

/* SysTick */
#define STK_BASE	0xe000e010ul

#define STK_CTRL	((uint32_t*)STK_BASE)
#define STK_ENABLE		0x00000001ul
#define STK_TICKINT		0x00000002ul
#define STK_CLKSOURCE	0x00000004ul
#define STK_COUNTFLAG	0x00010000ul

#define STK_LOAD	((uint32_t *)(STK_BASE+0x4))

#define STK_VAL		((uint32_t *)(STK_BASE+0x8))

/* STM32F407VG FEATURES */
/* Reset & Clock Control */
#define RCC_BASE 0x40023800ul

#define RCC_AHB1ENR ((uint32_t*)(RCC_BASE+0x30))
#define RCC_AHB1ENR_GPIOAEN			0x00000001ul
#define RCC_AHB1ENR_GPIOBEN			0x00000002ul
#define RCC_AHB1ENR_GPIOCEN			0x00000004ul
#define RCC_AHB1ENR_GPIODEN			0x00000008ul
#define RCC_AHB1ENR_GPIOEEN			0x00000010ul
#define RCC_AHB1ENR_GPIOFEN			0x00000020ul
#define RCC_AHB1ENR_GPIOGEN			0x00000040ul
#define RCC_AHB1ENR_GPIOHEN			0x00000080ul
#define RCC_AHB1ENR_GPIOIEN			0x00000100ul
#define RCC_AHB1ENR_CRCEN			0x00001000ul
#define RCC_AHB1ENR_BKPSRAMEN		0x00040000ul
#define RCC_AHB1ENR_CCMDATARAMEN	0x00100000ul
#define RCC_AHB1ENR_DMA1EN			0x00200000ul
#define RCC_AHB1ENR_DMA2EN			0x00400000ul
#define RCC_AHB1ENR_ETHMACEN		0x02000000ul
#define RCC_AHB1ENR_ETHMACTXEN		0x04000000ul
#define RCC_AHB1ENR_ETHMACRXEN		0x08000000ul
#define RCC_AHB1ENR_ETHMACPTPEN		0x10000000ul
#define RCC_AHB1ENR_OTGHSEN			0x20000000ul
#define RCC_AHB1ENR_OTGHSULPIEN		0x40000000ul

#define RCC_AHB2ENR ((uint32_t*)(RCC_BASE+0x34))
#define RCC_AHB2ENR_DCMIEN	0x00000001ul
#define RCC_AHB2ENR_CRYPEN	0x00000010ul
#define RCC_AHB2ENR_HASHEN	0x00000020ul
#define RCC_AHB2ENR_RNGEN	0x00000040ul
#define RCC_AHB2ENR_OTGFSEN	0x00000080ul

#define RCC_AHB3ENR ((uint32_t*)(RCC_BASE+0x38))
#define RCC_AHB3ENR_FSMCEN 0x00000001ul

#define RCC_APB1ENR ((uint32_t*)(RCC_BASE+0x40))
#define RCC_APB1ENR_TIM2EN		0x00000001ul
#define RCC_APB1ENR_TIM3EN		0x00000002ul
#define RCC_APB1ENR_TIM4EN		0x00000004ul
#define RCC_APB1ENR_TIM5EN		0x00000008ul
#define RCC_APB1ENR_TIM6EN		0x00000010ul
#define RCC_APB1ENR_TIM7EN		0x00000020ul
#define RCC_APB1ENR_TIM12EN		0x00000040ul
#define RCC_APB1ENR_TIM13EN		0x00000080ul
#define RCC_APB1ENR_TIM14EN		0x00000100ul
#define RCC_APB1ENR_WWDGEN		0x00000800ul
#define RCC_APB1ENR_SPI2EN		0x00004000ul
#define RCC_APB1ENR_SPI3EN		0x00008000ul
#define RCC_APB1ENR_USART2EN	0x00020000ul
#define RCC_APB1ENR_USART3EN	0x00040000ul
#define RCC_APB1ENR_USART4EN	0x00080000ul
#define RCC_APB1ENR_USART5EN	0x00100000ul
#define RCC_APB1ENR_I2C1EN		0x00200000ul
#define RCC_APB1ENR_I2C2EN		0x00400000ul
#define RCC_APB1ENR_I2C3EN		0x00800000ul
#define RCC_APB1ENR_CAN1EN		0x02000000ul
#define RCC_APB1ENR_CAN2EN		0x04000000ul
#define RCC_APB1ENR_PWREN		0x10000000ul
#define RCC_APB1ENR_DACEN		0x20000000ul

#define RCC_APB2ENR ((uint32_t*)(RCC_BASE+0x44))
#define RCC_APB2ENR_TIM1EN		0x00000001ul
#define RCC_APB2ENR_TIM8EN		0x00000002ul
#define RCC_APB2ENR_USART1EN	0x00000010ul
#define RCC_APB2ENR_USART6EN	0x00000020ul
#define RCC_APB2ENR_ADC1EN		0x00000100ul
#define RCC_APB2ENR_ADC2EN		0x00000200ul
#define RCC_APB2ENR_ADC3EN		0x00000400ul
#define RCC_APB2ENR_SDIO		0x00000800ul
#define RCC_APB2ENR_SPI1EN		0x00001000ul
#define RCC_APB2ENR_SPI4EN		0x00002000ul
#define RCC_APB2ENR_SYSCFGEN	0x00004000ul
#define RCC_APB2ENR_TIM9EN		0x00010000ul
#define RCC_APB2ENR_TIM10EN		0x00020000ul
#define RCC_APB2ENR_TIM11EN		0x00040000ul
#define RCC_APB2ENR_SPI5EN		0x00100000ul
#define RCC_APB2ENR_SPI6EN		0x00200000ul

/* General Purpose Input/Output */
#define GPIOA_BASE 0x40020000ul
#define GPIOB_BASE 0x40020400ul
#define GPIOC_BASE 0x40020800ul
#define GPIOD_BASE 0x40020C00ul
#define GPIOE_BASE 0x40021000ul
#define GPIOF_BASE 0x40021400ul
#define GPIOG_BASE 0x40021800ul
#define GPIOH_BASE 0x40021C00ul
#define GPIOI_BASE 0x40022000ul

#define GPIOx_MODER(base) ((uint32_t*)(base+0x00))
#define GPIOx_OTYPER(base) ((uint32_t*)(base+0x04))
#define GPIOx_OSPEEDR(base) ((uint32_t*)(base+0x08))
#define GPIOx_PUPDR(base) ((uint32_t*)(base+0x0c))
#define GPIOx_IDR(base) ((uint32_t*)(base+0x10))
#define GPIOx_ODR(base) ((uint32_t*)(base+0x14))
#define GPIOx_BSRR(base) ((uint32_t*)(base+0x18))
#define GPIOx_LCKR(base) ((uint32_t*)(base+0x1c))
#define GPIOx_AFRL(base) ((uint32_t*)(base+0x20))
#define GPIOx_AFRH(base) ((uint32_t*)(base+0x24))

/* Universal Synchronous Asynchronous Receiver Transmitter */
#define USART1_BASE	0x40011000ul
#define USART2_BASE	0x40004400ul
#define USART3_BASE	0x40004800ul
#define UART4_BASE	0x40004c00ul
#define UART5_BASE	0x40005000ul
#define USART6_BASE	0x40011400ul
#define UART7_BASE	0x40017800ul
#define UART8_BASE	0x40017C00ul

#define USARTx_SR(base) ((uint32_t*)(base+0x00))
#define USART_SR_PE	0x001ul
#define USART_SR_FE	0x002ul
#define USART_SR_NF	0x004ul
#define USART_SR_ORF	0x008ul
#define USART_SR_IDLE	0x010ul
#define USART_SR_RXNE	0x020ul
#define USART_SR_TC	0x040ul
#define USART_SR_TXE	0x080ul
#define USART_SR_LBD	0x100ul
#define USART_SR_CTS	0x200ul

#define USARTx_DR(base) ((uint32_t*)(base+0x04))
#define USARTx_BRR(base) ((uint32_t*)(base+0x08))

#define USARTx_CR1(base) ((uint32_t*)(base+0x0C))
#define USART_CR1_SBK	0x0001ul
#define USART_CR1_RWU	0x0002ul
#define USART_CR1_RE	0x0004ul
#define USART_CR1_TE	0x0008ul
#define USART_CR1_IDLEIE	0x0010ul
#define USART_CR1_RXNEIE	0x0020ul
#define USART_CR1_TCIE	0x0040ul
#define USART_CR1_TXEIE	0x0080ul
#define USART_CR1_PEIE	0x0100ul
#define USART_CR1_PS	0x0200ul
#define USART_CR1_PCE	0x0400ul
#define USART_CR1_WAKE	0x0800ul
#define USART_CR1_M	0x1000ul
#define USART_CR1_UE	0x2000ul
#define USART_CR1_OVER8	0x8000ul

#define USARTx_CR2(base) ((uint32_t*)(base+0x10))
#define USARTx_CR3(base) ((uint32_t*)(base+0x14))
#define USARTx_GTPR(base) ((uint32_t*)(base+0x18))

/* Analog Digital Converter */
#define ADC_BASE	0x40012000ul
#define ADC1_BASE	(ADC_BASE+0x000)
#define ADC2_BASE	(ADC_BASE+0x100)
#define ADC3_BASE	(ADC_BASE+0x200)
#define ADC_COMMON_BASE	(ADC_BASE+0x300)

#define ADCx_SR(base) ((uint32_t*)(base+0x00))
#define ADC_SR_AWD		0x00000001ul
#define ADC_SR_EOC		0x00000002ul
#define ADC_SR_JEOC		0x00000004ul
#define ADC_SR_JSTRT	0x00000008ul
#define ADC_SR_STRT		0x00000010ul
#define ADC_SR_OVR		0x00000020ul

#define ADCx_CR1(base) ((uint32_t*)(base+0x04))
#define ADCx_CR2(base) ((uint32_t*)(base+0x08))
#define ADCx_SMPR1(base) ((uint32_t*)(base+0x0c))
#define ADCx_SMPR2(base) ((uint32_t*)(base+0x10))
#define ADCx_JOFR1(base) ((uint32_t*)(base+0x14))
#define ADCx_JOFR2(base) ((uint32_t*)(base+0x18))
#define ADCx_JOFR3(base) ((uint32_t*)(base+0x1c))
#define ADCx_JOFR4(base) ((uint32_t*)(base+0x20))
#define ADCx_HTR(base) ((uint32_t*)(base+0x24))
#define ADCx_LTR(base) ((uint32_t*)(base+0x28))
#define ADCx_SQR1(base) ((uint32_t*)(base+0x2c))
#define ADCx_SQR2(base) ((uint32_t*)(base+0x30))
#define ADCx_SQR3(base) ((uint32_t*)(base+0x34))
#define ADCx_JSQR(base) ((uint32_t*)(base+0x38))
#define ADCx_JDR1(base) ((uint32_t*)(base+0x3c))
#define ADCx_JDR2(base) ((uint32_t*)(base+0x40))
#define ADCx_JDR3(base) ((uint32_t*)(base+0x44))
#define ADCx_JDR4(base) ((uint32_t*)(base+0x48))
#define ADCx_DR(base) ((uint32_t*)(base+0x4c))

/* Random Number Generator */

#define RNG_BASE 0x50060800ul

#define RNG_CR	((uint32_t*)(RNG_BASE+0x00))
#define RNG_CR_RNGEN	0x00000004ul
#define RNG_CR_IE		0x00000008ul

#define RNG_SR	((uint32_t*)(RNG_BASE+0x04))
#define RNG_SR_DRDY		0x00000001ul
#define RNG_SR_CECS		0x00000002ul
#define RNG_SR_SECS		0x00000004ul
#define RNG_SR_CEIS		0x00000002ul
#define RNG_SR_SEIS		0x00000004ul

#define RNG_DR	((uint32_t*)(RNG_BASE+0x08))
