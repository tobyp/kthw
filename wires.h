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

#ifndef WIRES_H_
#define WIRES_H_

#include <stdint.h>

#include "bomb.h"
#include "util.h"

struct wires {
	struct module module;
	struct shreg * shreg;
	struct adc * adc;

	uint8_t ticks;
	uint8_t wires[8];
	uint8_t count;
	uint8_t morituri; //index of wire that needs to be cut
};

void wires_prepare_tick(struct bomb * bomb, struct module * module);
void wires_tick(struct bomb * bomb, struct module * module);

#define WIRES_MOD_INIT {"simple wires", 0, &wires_prepare_tick, &wires_tick, NULL, NULL}

#endif
