#include "morse.h"
#include "util.h"

struct morse_seq morse_seqs[] = {
	{{0xa8, 0xaa, 0x22, 0xea, 0x2e, 0xa0, 0x0}, 50, 3505}, /* shell */
	{{0xaa, 0x2e, 0x2e, 0xa2, 0xea, 0x2a, 0x0}, 54, 3515}, /* halls */
	{{0xa8, 0xba, 0x8a, 0x3a, 0xe8, 0xeb, 0x80}, 56, 3522}, /* slick */
	{{0xe2, 0xe8, 0xa3, 0xae, 0x8e, 0xb8, 0x0}, 52, 3532}, /* trick */
	{{0xea, 0x8e, 0xee, 0x3a, 0xb8, 0x8a, 0x80}, 56, 3535}, /* boxes */
	{{0xba, 0x88, 0xb8, 0xeb, 0x8a, 0x80}, 48, 3542}, /* leaks */
	{{0xa8, 0xe2, 0xe8, 0xee, 0xe3, 0xaa, 0x20, 0x0}, 58, 3545}, /* strobe */
	{{0xea, 0x8a, 0x2a, 0x38, 0xba, 0x3b, 0xb8, 0x0}, 60, 3552}, /* bistro */
	{{0xae, 0x8b, 0xa8, 0xa3, 0xae, 0x8e, 0xb8, 0x0}, 60, 3555}, /* flick */
	{{0xea, 0x8e, 0xee, 0x3b, 0x8e, 0xa8, 0xa8, 0x0}, 60, 3565}, /* bombs */
	{{0xea, 0x8b, 0xa2, 0x2e, 0x3a, 0xe0, 0x0}, 50, 3572}, /* break */
	{{0xea, 0x8b, 0xa2, 0x8e, 0xba, 0x3a, 0xe0, 0x0}, 58, 3575}, /* brick */
	{{0xa8, 0xe2, 0x2e, 0x3a, 0xe0, 0x0}, 42, 3582}, /* steak */
	{{0xa8, 0xe2, 0x8e, 0x8e, 0xe8, 0x0}, 44, 3592}, /* sting */
	{{0xab, 0x88, 0xeb, 0xa3, 0x8e, 0xee, 0x2e, 0x80}, 64, 3595}, /* vector */
	{{0xea, 0x88, 0xb8, 0xe2, 0xa0, 0x0}, 42, 3600}, /* beats */
};



void morse_init(struct bomb * bomb, struct morse * morse, struct gpio * out_led, struct gpio * in_btn, struct adc * adc, struct shreg * freq0, struct shreg * freq1, struct shreg * freq2, struct shreg * freq3) {
	morse->mod.flags = 0;
	morse->mod.tick = &morse_tick;
	morse->mod.next = NULL;
	morse->ticks = 0;
	morse->seq = &morse_seqs[rnd() % (sizeof(morse_seqs) / sizeof(struct morse_seq))];
	morse->button_cache = 0;
	morse->out_led = out_led;
	morse->in_btn = in_btn;
	morse->adc = adc;
	morse->freq[0] = freq0;
	morse->freq[1] = freq1;
	morse->freq[2] = freq2;
	morse->freq[3] = freq3;
}

void morse_tick(struct bomb * bomb, struct module * mod) {
	struct morse * morse = (struct morse *)mod;

	morse->ticks = (morse->ticks + 1) % (TICKS_PER_DOT * morse->seq->bits);
	uint32_t dots = morse->ticks / TICKS_PER_DOT;

	if (morse->seq->dots[dots / 8] & (0x80 >> (dots % 8))) {
		*morse->out_led->reg |= morse->out_led->mask;
	}
	else {
		*morse->out_led->reg &= ~morse->out_led->mask;
	}

	uint16_t freq = morse->adc->value * 120 / 4096 + 3482;
	morse->freq[0]->value = freq / 1 % 10;
	morse->freq[1]->value = freq / 10 % 10;
	morse->freq[2]->value = freq / 100 % 10;
	morse->freq[3]->value = freq / 1000 % 10;

	uint8_t value = (*morse->in_btn->reg & morse->in_btn->mask) ? 1 : 0;
	if (morse->button_cache != value) {
		morse->button_cache = value;
		if (value) {
			if (freq >= morse->seq->freq - 1 && freq <= morse->seq->freq + 1) {
				print("morse: disarmed\n");
				mod->flags |= MOD_DONE;
				*morse->out_led->reg &= ~morse->out_led->mask;
				return;
			}
			else {
				strike(bomb);
				morse->ticks = 0;
			}
		}
	}
}
