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

#ifndef CAPACITOR_H_
#define CAPACITOR_H_

#include <stdint.h>

#include "bomb.h"
#include "util.h"

/* The capacitor is a needy module that can never be completed.
It will randomly generate a capacity between CAP_CAPACITY_MIN(timer) and CAP_CAPACITY_MAX(timer) at initialization.
When the button is not held, it will charge up by CAP_CHARGE_PER_TICK, when the button is held down, it will discharge by CAP_DISCHARGE_PER_TICK.
If the capacitor is ever charged to capacity, it will explode the bomb. */

#define CAP_CHARGE_PER_TICK 1  // add this much charge per tick, when the button is not pressed.
#define CAP_DISCHARGE_PER_TICK 5  // remove this much charge per tick when the button is down.

#define CAP_CAPACITY_MIN(t)	CAP_CHARGE_PER_TICK * TICKS_PER_SEC * 50
#define CAP_CAPACITY_MAX(t)	CAP_CHARGE_PER_TICK * TICKS_PER_SEC * 100

struct capacitor {
	struct module module;
	struct gpio * in_btn;
	struct shreg * bargraph[2];

	uint16_t capacity;
	uint16_t charge;
};

void capacitor_prepare_tick(struct bomb * bomb, struct module * module);
void capacitor_tick(struct bomb * bomb, struct module * module);
void capacitor_reset(struct bomb * bomb, struct module * module);

#define CAPACITOR_MOD_INIT {"capacitor", MF_NEEDY, &capacitor_prepare_tick, &capacitor_tick, &capacitor_reset, NULL}
#endif
