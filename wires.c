#include "wires.h"

#include "util.h"

int wires_prepare_tick(struct bomb * bomb, struct module * module) {
	struct wires * wires = (struct wires *)module;

	if (wires->ticks != 0) {
		uint8_t wire_index = (wires->ticks - 1) % 8;
		uint8_t wire_mask = 1 << wire_index;
		uint8_t wire_value = (*wires->in->reg & wires->in->mask) ? wire_mask : 0;
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
		return 1;
	}

	return 0;
}

int wires_tick(struct bomb * bomb, struct module * module) {
	struct wires * wires = (struct wires *)module;

	uint8_t wire_index = wires->ticks % 8;
	uint8_t wire_mask = 1 << wire_index;
	uint8_t wire_value = (*wires->in->reg & wires->in->mask) ? wire_mask : 0;

	if ((wires->cache & wire_mask) ^ wire_value) { //a wire has changed!
		printf("[%s] wires=%x->", wires->cache);
		wires->cache = (wires->cache & ~wire_mask) | wire_value;
		printf("%s\n", wires->cache);

		if (!wire_value) { //wire was removed
			if (!(wires->removed & wire_mask)) { //never removed before
				wires->removed |= wire_mask;
				if (wire_mask & wires->morituri) { //a correct one
					printf("\t(removed correctly)\n");
					if (!(wires->cache & wires->morituri)) { //no wire remains to be cut
						return 1;
					}
				}
				else {
					strike(bomb);
				}
			}
		}
		else {
			printf("\t(added)\n");
		}
	}

	wires->ticks = (wires->ticks + 1) % 8;
	wire_index = wires->ticks % 8;
	wire_mask = 1 << wire_index;
	wires->shreg->value = wire_mask;

	return 0;
}
