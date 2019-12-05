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

#ifndef SIMONSAYS_H_
#define SIMONSAYS_H_

#include <stdint.h>

#include "bomb.h"
#include "util.h"

struct simonsays {
	struct module module;
	struct gpio * in_btn;
	struct shreg * sr;

	uint16_t ticks;
	uint16_t button_countdown;
	uint8_t expected_index;
	int8_t button_caches[4];
	uint8_t seq[6];
	uint8_t stage_count;
	uint8_t stage;
};

void simonsays_prepare_tick(struct bomb * bomb, struct module * module);
void simonsays_tick(struct bomb * bomb, struct module * module);
void simonsays_reset(struct bomb * bomb, struct module * module);

#define SIMONSAYS_MOD_INIT {"simon says", 0, &simonsays_prepare_tick, &simonsays_tick, &simonsays_reset, NULL}

#endif
