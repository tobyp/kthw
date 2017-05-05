#ifndef MEMORY_H_
#define MEMORY_H_

#include <stdint.h>

#include "bomb.h"
#include "util.h"

struct memory {
	struct module module;
	struct gpio * in_btn;
	struct shreg * sr_btn;
	struct shreg * sr_stage;
	struct shreg * sr_display;
	struct shreg * sr_btn_lbls[4];

	uint8_t ticks;
	uint8_t display;
	uint8_t lbl_hist[4];
	uint8_t pos_hist[4];
	uint8_t buttons[4];
	uint8_t stage;
	uint8_t btn_cache;
};

void memory_prepare_tick(struct bomb * bomb, struct module * module);
void memory_tick(struct bomb * bomb, struct module * module);
void memory_reset(struct bomb * bomb, struct module * module);

#define MEMORY_MOD_INIT {"memory", 0, &memory_prepare_tick, &memory_tick, &memory_reset, NULL}

#endif
