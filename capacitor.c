#include "capacitor.h"

int capacitor_prepare_tick(struct bomb * bomb, struct module * module) {
	struct capacitor * capacitor = (struct capacitor *)module;

	capacitor->capacity = CAP_CAPACITY_MIN + rnd() % (CAP_CAPACITY_MAX - CAP_CAPACITY_MIN);
	print("capacitor: "); print_uint(capacitor->capacity); print("\n");

	return 1;
}

int capacitor_tick(struct bomb * bomb, struct module * module) {
	struct capacitor * capacitor = (struct capacitor *)module;

	if (capacitor->charge == capacitor->capacity) {
		explode(bomb);
	}

	if (*capacitor->in_btn->reg & capacitor->in_btn->mask) {
		if (capacitor->charge <= CAP_DISCHARGE_PER_TICK) {
			capacitor->charge = 0;
			capacitor->capacity = CAP_CAPACITY_MIN + rnd() % (CAP_CAPACITY_MAX - CAP_CAPACITY_MIN);
			print("capacitor: "); print_uint(capacitor->capacity); print("\n");
		}
		else {
			capacitor->charge -= CAP_DISCHARGE_PER_TICK;
		}
	}
	else {
		capacitor->charge = clamp(capacitor->charge + CAP_CHARGE_PER_TICK, 0, capacitor->capacity);
		if (capacitor->charge >= capacitor->capacity) {
			explode(bomb);
		}
	}

	uint16_t bars = capacitor->charge * 16 / capacitor->capacity;
	bars = (1 << bars) - 1;
	capacitor->sr[0]->value = bars & 0xff;
	capacitor->sr[1]->value = (bars >> 8) & 0xff;

	return 0;
}

void capacitor_reset(struct bomb * bomb, struct module * module) {
	struct capacitor * capacitor = (struct capacitor *)module;

	capacitor->sr[0]->value = 0;
	capacitor->sr[1]->value = 0;
}
