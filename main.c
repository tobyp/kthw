 #include <stdint.h>

#include "stm32f407vg.h"

/*#define MASK_SER 0x100ul	//B8
#define MASK_SRCLK 0x200ul	//B9
#define MASK_RCLK 0x400ul	//B10 */
#define MASK_DONE 0x800ul	//B11
#define MASK_BLINK 0x1000ul	//B12
#define MASK_BTN_IN 0x2000ul	//B13

struct shift_register {
	uint32_t * reg;
	uint16_t mask_ser;
	uint16_t mask_srclk;
	uint16_t mask_rclk;
	//uint16_t mask_oe;
	//uint16_t mask_srclr;
};


struct simonsays {
	uint16_t tick_counter;
	uint8_t seq_out [6];
	struct shift_register *sr;
	//uint16_t mask_btn_in;
	uint8_t phase;
};


struct shift_register sr_simon = {GPIOB_ODR, 0x100ul, 0x200ul, 0x400ul};
struct simonsays simonsays = {0,{1,2,4,8,4,2}, &sr_simon, 0};

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

uint8_t v = 0x11;
//uint32_t systick_counter = 0;

void simonsays_tick(struct simonsays *ss) {
	uint32_t x = ss->tick_counter % 5000;
	if (x <= 2500) {
		v = ss->seq_out[ss->tick_counter / 5000];
	}
	else {
		v = 0;
	}

	/*if (systick_counter == 0){
		v = ss->seq_out[0];
		//sr_write(ss->sr,v);
	}
	else if (systick_counter == 2500){
		v = 0;
		//sr_write(ss->sr,v);
	}
	if (systick_counter == 5000  && ss->phase >= 1){
		v = ss->seq_out[1];
		//sr_write(ss->sr,v);
	}
	if (systick_counter == 7500){
		v = 0;
		//sr_write(ss->sr,v);
	}
	if (systick_counter == 10000 && ss->phase >= 2){
		v = ss->seq_out[2];
		//sr_write(ss->sr,ss->seq_out[2]);
	}
	if (systick_counter == 12500){
		v = 0;
		//sr_write(ss->sr,0);
	}
	if (systick_counter == 15000 && ss->phase >= 3){
		v = ss->seq_out[3];
		//sr_write(ss->sr,ss->seq_out[3]);
	}
	if (systick_counter == 17500){
		v = 0;
		//sr_write(ss->sr,0);
	}
	if (systick_counter == 20000 && ss->phase >= 4){
		v = ss->seq_out[4];
		//sr_write(ss->sr,ss->seq_out[4]);
	}
	if (systick_counter == 22500){
		v = 0;
		//sr_write(ss->sr,0);
	}
	if (systick_counter == 25000 && ss->phase >= 5){
		v = ss->seq_out[5];
		//sr_write(ss->sr,ss->seq_out[5]);
	}
	if (systick_counter == 27500){
		v = 0;
		//sr_write(ss->sr,0);
	} */
	switch (ss->tick_counter % 4) {
		case 0: v = 16 | v; break;
		case 1: v = 32 | v; break; 
		case 2: v = 64 | v; break; 
		case 3: v = 128 | v;break;
	}

	sr_write(ss->sr,v);
	ss->tick_counter = (ss->tick_counter +1) % 25001;

	uint8_t btn_val = (*GPIOB_IDR & MASK_BTN_IN) >> 12;
	if (btn_val) {
		*GPIOB_ODR |= MASK_BLINK;
	}
	else {
		*GPIOB_ODR &= ~MASK_BLINK;
	}
}

void __isr_systick() {
	//*GPIOD_ODR ^= 0x1000;

	/*v = ((v << 7) | (v >> 1));
	sr_write(&sr_simon, v);*/
	
	
	/*uint8_t btn_val = (*GPIOB_IDR & MASK_BTN_IN) >> 12;
	if (btn_val) {
		*GPIOB_ODR |= MASK_BLINK;
	}
	else {
		*GPIOB_ODR &= ~MASK_BLINK;
	}*/
	
	/*systick_counter++;
	if (systick_counter > 125000)
		systick_counter = 0;*/
	simonsays_tick(&simonsays);
} 

uint8_t what_button(uint8_t flash) {
	return flash << 4; //Platzhalter
}	//Eingabe: simonsays.seq_out[i]; Ausgabe: Zugehöriger Knopf (siehe Tabelle)


void main() {
	*RCC_AHB1ENR |= RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOBEN;

	*NVIC_PRI3 &= 0xff000000ul;
	*NVIC_PRI3 |= 0x0f000000ul;

	*GPIOD_MODER &= 0x3000000ul;
	*GPIOD_MODER |= 0x1000000ul; //D12 (onboard LED) out

	*GPIOB_MODER &= 0xfff0000ul;
	*GPIOB_MODER |= 0x1550000ul; //B8-12 out, B13 in

	*GPIOB_PUPDR &= 0xc000000ul;
	*GPIOB_PUPDR |= 0x8000000ul; //B13 pull-down

	*STK_LOAD = 1000000ul;
	*STK_VAL = 0;
	*STK_CTRL |= (STK_TICKINT | STK_ENABLE);

	while (1) { }
}
