#ifndef CAPACITOR_H_
#define CAPACITOR_H_

#include <stdint.h>

#include "bomb.h"
#include "util.h"

#define CAP_CHARGE_PER_TICK	1
#define CAP_DISCHARGE_PER_TICK	5
#define CAP_CAPACITY_MIN(t)	CAP_CHARGE_PER_TICK * TICKS_PER_SEC * 50 //(CAP_CHARGE_PER_TICK * TICKS_PER_SEC * 20 * (t) / 100)
#define CAP_CAPACITY_MAX(t)	CAP_CHARGE_PER_TICK * TICKS_PER_SEC * 100 //(CAP_CHARGE_PER_TICK * TICKS_PER_SEC * 33 * (t) / 100)

struct capacitor {
	struct module module;
	struct gpio * in_btn;
	struct shreg * sr[2];

	uint16_t capacity;
	uint16_t charge;
};

int capacitor_prepare_tick(struct bomb * bomb, struct module * module);
int capacitor_tick(struct bomb * bomb, struct module * module);
void capacitor_reset(struct bomb * bomb, struct module * module);

#define CAPACITOR_MOD_INIT {0, "capacitor", &capacitor_prepare_tick, &capacitor_tick, &capacitor_reset, NULL}
#endif
