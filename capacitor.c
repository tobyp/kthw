#include "capacitor.h"

void capacitor_prepare_tick(struct bomb * bomb, struct module * module) {
	struct capacitor * capacitor = (struct capacitor *)module;

	module->flags |= MF_NEEDY;
	capacitor->charge = 0;
	capacitor->capacity = CAP_CAPACITY_MIN(bomb->timer) + rnd() % (CAP_CAPACITY_MAX(bomb->timer) - CAP_CAPACITY_MIN(bomb->timer));
	printf("[%s] capacity=%d\n", module->name, capacitor->capacity);

	capacitor->sr[0]->value = 0;
	capacitor->sr[1]->value = 0;

	module->flags |= MF_READY;
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
	capacitor->sr[0]->value = bars & 0xff;
	capacitor->sr[1]->value = (bars >> 8) & 0xff;
}

void capacitor_reset(struct bomb * bomb, struct module * module) {
	struct capacitor * capacitor = (struct capacitor *)module;

	capacitor->sr[0]->value = 0;
	capacitor->sr[1]->value = 0;
}
