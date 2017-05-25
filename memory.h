/* KTHW - Hardware Clone of Keep Talking and Nobody Explodes
Copyright (C) 2017 Toby P., Thomas H.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>. */

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
	uint8_t stage;
	uint8_t buttons[4];
	uint8_t lbl_hist[4];  // label pressed in stage N
	uint8_t pos_hist[4];  // position pressed in stage N
	uint8_t btn_cache;
};

void memory_prepare_tick(struct bomb * bomb, struct module * module);
void memory_tick(struct bomb * bomb, struct module * module);
void memory_reset(struct bomb * bomb, struct module * module);

#define MEMORY_MOD_INIT {"memory", 0, &memory_prepare_tick, &memory_tick, &memory_reset, NULL}

#endif
