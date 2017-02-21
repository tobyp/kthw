#define RCC_BASE 0x40023800ul

#define RCC_CR ((uint32_t *)RCC_BASE)
#define HSEON 0x00010000ul
#define HSERDY 0x00020000ul
#define HSION 0x00000001ul
#define PLL_ON 0x01000000ul
#define PLL_RDY 0x02000000ul

#define RCC_PLLCFGR ((uint32_t *)RCC_BASE+0x4)
#define PLLSRC 0x00400000ul

#define RCC_CFGR ((uint32_t *)RCC_BASE+0x8)
#define SW1 0x00000002ul

#define STK_BASE 0xe000e010ul

#define STK_CTRL ((uint32_t *)STK_BASE)
#define STK_ENABLE 0x00000001ul
#define STK_TICKINT 0x00000002ul
#define STK_CLKSOURCE 0x00000004ul
#define STK_COUNTFLAG 0x00010000ul

#define STK_LOAD ((uint32_t *)STK_BASE+0x4)
#define STK_VAL ((uint32_t *)STK_BASE+0x8)