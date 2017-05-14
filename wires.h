#ifndef WIRES_H_
#define WIRES_H_

#include <stdint.h>

#include "bomb.h"

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
