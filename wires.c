#include "wires.h"

#include "util.h"

void wires_prepare_tick(struct bomb * bomb, struct module * module) {
	struct wires * wires = (struct wires *)module;

	if (wires->ticks != 0) {
		uint8_t wire_index = (wires->ticks - 1) % 8;
		uint8_t wire_mask = 1 << wire_index;
		uint8_t wire_value = (gpio_get(wires->in)) ? wire_mask : 0;
		wires->morituri |= wire_value;
	}

	wires->ticks = (wires->ticks + 1);
	uint8_t wire_index = (wires->ticks - 1) % 8;
	uint8_t wire_mask = 1 << wire_index;
	wires->shreg->value = wire_mask;

	if (wires->ticks == 9) {
		wires->ticks = 0;
		wires->cache = wires->morituri;
		printf("[%s] morituri=%x\n", module->name, wires->morituri);
		module->flags |= MF_READY;
		if (wires->morituri == 0x0) {
			printf("[%s] WARNING: no wires, module starts out completed\n", module->name);
			module->flags |= MF_COMPLETE;
		}
	}
}

void wires_tick(struct bomb * bomb, struct module * module) {
	struct wires * wires = (struct wires *)module;

	uint8_t wire_index = wires->ticks % 8;
	uint8_t wire_mask = 1 << wire_index;
	uint8_t wire_value = (gpio_get(wires->in)) ? wire_mask : 0;

	if ((wires->cache & wire_mask) ^ wire_value) { //a wire has changed!
		printf("[%s] wires=%x->", module->name, wires->cache);
		wires->cache = (wires->cache & ~wire_mask) | wire_value;
		printf("%x\n", wires->cache);

		if (!wire_value) { //a wire was removed
			if (!(wires->removed & wire_mask)) { //for the first time
				wires->removed |= wire_mask;
				if (!(wire_mask & wires->morituri)) { //the wrong one
					printf("[%s] (wire removed incorrectly)\n", module->name);
					strike(bomb, module);
				}
				else {
					printf("[%s] (wire removed correctly)\n", module->name);
				}
			}
		}
		else { //a wire was added
			printf("[%s] (wire added)\n", module->name);
		}
	}

	if (!(wires->cache & wires->morituri)) { //no wire remains to be cut
		module->flags |= MF_COMPLETE;
		return;
	}

	wires->ticks = (wires->ticks + 1) % 8;
	wire_index = wires->ticks % 8;
	wire_mask = 1 << wire_index;
	wires->shreg->value = wire_mask;
}
