#ifndef SHIFT_REGISTER_H_
#define SHIFT_REGISTER_H_

#include <stdint.h>

struct shift_register {
	uint32_t * reg;
	uint16_t mask_ser;
	uint16_t mask_srclk;
	uint16_t mask_rclk;
	//uint16_t mask_oe;
	//uint16_t mask_srclr;
};

void sr_write(struct shift_register *sr, uint8_t value);

#endif
