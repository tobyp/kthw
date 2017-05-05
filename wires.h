#ifndef WIRES_H_
#define WIRES_H_

#include <stdint.h>

#include "bomb.h"

struct wires {
	struct module module;
	struct shreg * shreg;
	struct gpio * in;

	uint8_t ticks;
	uint8_t morituri;  //wires that have to be removed to win
	uint8_t removed;  //removing an already-removed wire should do fuck all.
	uint8_t cache;
};

void wires_prepare_tick(struct bomb * bomb, struct module * module);
void wires_tick(struct bomb * bomb, struct module * module);

#define WIRES_MOD_INIT {"simple wires", 0, &wires_prepare_tick, &wires_tick, NULL, NULL}

#endif
