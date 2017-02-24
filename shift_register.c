#include "shift_register.h"

void sr_write(struct shift_register *sr, uint8_t value) {
	for (uint8_t i=0; i<8; ++i) {
		if (value & 0x1) {
			*sr->reg |= sr->mask_ser;
		}
		else {
			*sr->reg &= ~sr->mask_ser;
		}
		*sr->reg |= sr->mask_srclk;
		value >>= 1;
		__asm__("nop");
		*sr->reg &= ~sr->mask_srclk;
	}
	*sr->reg |= sr->mask_rclk; __asm__("nop"); __asm__("nop"); *sr->reg &= ~sr->mask_rclk;
}