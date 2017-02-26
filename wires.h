#ifndef WIRES_H_
#define WIRES_H_

#include <stdint.h>

#include "bomb.h"

struct wires {
	struct module module;
	struct gpio * in_wire[6];

	uint8_t wires_to_cut;
	uint8_t wire_cache;
};

int wires_prepare_tick(struct bomb * bomb, struct module * module);
int wires_tick(struct bomb * bomb, struct module * module);

#define WIRES_MOD_INIT {0, "simple wires", &wires_prepare_tick, &wires_tick, NULL, NULL}

#endif
