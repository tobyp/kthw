/* CORTEX-M FEATURES */
/* Nested Vector Interrupt Controller */
#define NVIC_BASE 0xe000e100ul

#define NVIC_PRIn(n) ((uint32_t*)(NVIC_BASE+0x300+4*(n)))
#define NVIC_PRI0 NVIC_PRIn(0)
#define NVIC_PRI1 NVIC_PRIn(1)
#define NVIC_PRI2 NVIC_PRIn(2)
#define NVIC_PRI3 NVIC_PRIn(3)
#define NVIC_PRI4 NVIC_PRIn(4)
#define NVIC_PRI5 NVIC_PRIn(5)
#define NVIC_PRI6 NVIC_PRIn(6)
#define NVIC_PRI7 NVIC_PRIn(7)
#define NVIC_PRI8 NVIC_PRIn(8)
#define NVIC_PRI9 NVIC_PRIn(9)

/* SysTick */
#define STK_BASE 0xe000e010ul

#define STK_CTRL ((uint32_t*)STK_BASE)
#define STK_ENABLE 0x00000001ul
#define STK_TICKINT 0x00000002ul
#define STK_CLKSOURCE 0x00000004ul
#define STK_COUNTFLAG 0x00010000ul

#define STK_LOAD ((uint32_t *)(STK_BASE+0x4))
#define STK_VAL ((uint32_t *)(STK_BASE+0x8))

/* STM32F407VG FEATURES */
/* Reset & Clock Control */
#define RCC_BASE 0x40023800ul
#define RCC_AHB1ENR ((uint32_t*)(RCC_BASE+0x30))
#define RCC_AHB1ENR_GPIOAEN 0x1ul
#define RCC_AHB1ENR_GPIOBEN 0x2ul
#define RCC_AHB1ENR_GPIOCEN 0x4ul
#define RCC_AHB1ENR_GPIODEN 0x8ul

/* General Purpose Input/Output */
#define GPIOx_MODER(base) ((uint32_t*)(base+0x00))
#define GPIOx_OTYPER(base) ((uint32_t*)(base+0x04))
#define GPIOx_OSPEEDR(base) ((uint32_t*)(base+0x08))
#define GPIOx_PUPDR(base) ((uint32_t*)(base+0x0c))
#define GPIOx_IDR(base) ((uint32_t*)(base+0x10))
#define GPIOx_ODR(base) ((uint32_t*)(base+0x14))

#define GPIOA_BASE 0x40020000ul
#define GPIOA_MODER GPIOx_MODER(GPIOA_BASE)
#define GPIOA_OTYPER GPIOx_OTYPER(GPIOA_BASE)
#define GPIOA_OSPEEDR GPIOx_OSPEEDR(GPIOA_BASE)
#define GPIOA_PUPDR GPIOx_PUPDR(GPIOA_BASE)
#define GPIOA_IDR GPIOx_IDR(GPIOA_BASE)
#define GPIOA_ODR GPIOx_ODR(GPIOA_BASE)

#define GPIOB_BASE 0x40020400ul
#define GPIOB_MODER GPIOx_MODER(GPIOB_BASE)
#define GPIOB_OTYPER GPIOx_OTYPER(GPIOB_BASE)
#define GPIOB_OSPEEDR GPIOx_OSPEEDR(GPIOB_BASE)
#define GPIOB_PUPDR GPIOx_PUPDR(GPIOB_BASE)
#define GPIOB_IDR GPIOx_IDR(GPIOB_BASE)
#define GPIOB_ODR GPIOx_ODR(GPIOB_BASE)

#define GPIOC_BASE 0x40020800ul
#define GPIOC_MODER GPIOx_MODER(GPIOC_BASE)
#define GPIOC_OTYPER GPIOx_OTYPER(GPIOC_BASE)
#define GPIOC_OSPEEDR GPIOx_OSPEEDR(GPIOC_BASE)
#define GPIOC_PUPDR GPIOx_PUPDR(GPIOC_BASE)
#define GPIOC_IDR GPIOx_IDR(GPIOC_BASE)
#define GPIOC_ODR GPIOx_ODR(GPIOC_BASE)

#define GPIOD_BASE 0x40020C00ul
#define GPIOD_MODER GPIOx_MODER(GPIOD_BASE)
#define GPIOD_OTYPER GPIOx_OTYPER(GPIOD_BASE)
#define GPIOD_OSPEEDR GPIOx_OSPEEDR(GPIOD_BASE)
#define GPIOD_PUPDR GPIOx_PUPDR(GPIOD_BASE)
#define GPIOD_IDR GPIOx_IDR(GPIOD_BASE)
#define GPIOD_ODR GPIOx_ODR(GPIOD_BASE)
