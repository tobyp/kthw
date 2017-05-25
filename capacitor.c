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

#include "capacitor.h"

void capacitor_prepare_tick(struct bomb * bomb, struct module * module) {
	struct capacitor * capacitor = (struct capacitor *)module;

	capacitor->capacity = rnd_range(CAP_CAPACITY_MIN(bomb->timer), CAP_CAPACITY_MAX(bomb->timer));
	printf("[%s] capacity=%d\n", module->name, capacitor->capacity);
	capacitor->charge = 0;

	capacitor->bargraph[0]->value = 0;
	capacitor->bargraph[1]->value = 0;

	module->flags |= MF_NEEDY | MF_READY;
}

void capacitor_tick(struct bomb * bomb, struct module * module) {
	struct capacitor * capacitor = (struct capacitor *)module;

	if (capacitor->charge >= capacitor->capacity) {
		explode(bomb, module->name);
	}

	if (gpio_get(capacitor->in_btn)) {
		if (capacitor->charge <= CAP_DISCHARGE_PER_TICK) {
			capacitor->charge = 0;
		}
		else {
			capacitor->charge -= CAP_DISCHARGE_PER_TICK;
		}
	}
	else {
		capacitor->charge = clamp(capacitor->charge + CAP_CHARGE_PER_TICK, 0, capacitor->capacity);
	}

	uint32_t bars = capacitor->charge * 16 / capacitor->capacity;
	bars = (1ul << bars) - 1;
	capacitor->bargraph[0]->value = bars & 0xff;
	capacitor->bargraph[1]->value = (bars >> 8) & 0xff;
}

void capacitor_reset(struct bomb * bomb, struct module * module) {
	struct capacitor * capacitor = (struct capacitor *)module;

	capacitor->bargraph[0]->value = 0;
	capacitor->bargraph[1]->value = 0;
}
