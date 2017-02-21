#include <stdint.h>

#include "stm32f407vg.h"

void __isr_systick() {
	
}

#define SYSTICK_INTERVAL 0xFFFFFF

void main() {
	*STK_LOAD |= SYSTICK_INTERVAL;
	*STK_CTRL |= (STK_TICKINT | STK_ENABLE);
}
