#include <stdint.h>
#include <stddef.h>

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

#define BOMB_EXPLODED 0x1
#define STRIKE_LIMIT 3
#define TICKS_PER_SEC 10000

struct bomb {
	uint8_t flags;
	uint32_t ticks;
	uint8_t strikes;

	struct shift_register * sr_timer[3];
	struct shift_register * sr_strikes;
};

struct bomb bomb = {0, 0xFFFFFFFF, 0, {NULL, NULL, NULL}, NULL};


void explode() { }

uint8_t sevenseg_digits[] = {0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xFA,0xE0,0xFE,0xF6};

int bomb_tick(struct bomb * bomb) {
	if (bomb->flags & BOMB_EXPLODED) return 1;
	if (bomb->ticks) bomb->ticks--;
	if (bomb->ticks == 0 || bomb->strikes == STRIKE_LIMIT) {
		bomb->flags |= BOMB_EXPLODED;
		explode();
		return 1;
	}
	uint32_t secs = bomb->ticks / TICKS_PER_SEC;
	//sr_write(bomb->sr_timer[0], sevenseg_digits[secs / 1 % 10]);
	//sr_write(bomb->sr_timer[1], sevenseg_digits[secs / 10 % 10]);
	//sr_write(bomb->sr_timer[2], sevenseg_digits[secs / 100 % 10]);
	//sr_write(bomb->sr_strikes, (1 << bomb->strikes) - 1);
}

uint8_t v = 0x11;
void simonsays_tick(struct simonsays *ss) {
	uint32_t x = ss->tick_counter % 5000;
	if (x <= 2500) {
		v = ss->seq_out[ss->tick_counter / 5000];
	}
	else {
		v = 0;
	}
	v |= 1 << ((ss->tick_counter % 4) + 4);

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
	*GPIOD_ODR ^= 0x1000;

	if (bomb_tick(&bomb)) {
		simonsays_tick(&bomb, &simonsays);
	}
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

	*STK_LOAD = 200ul;
	*STK_VAL = 0;
	*STK_CTRL |= (STK_TICKINT | STK_ENABLE);

	while (1) { }
}
