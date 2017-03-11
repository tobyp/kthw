#include "wires.h"

#include "util.h"

int wires_prepare_tick(struct bomb * bomb, struct module * module) {
	struct wires * wires = (struct wires *)module;

	for (uint8_t i=0; i<6; ++i) {
		uint8_t wire_value = (*wires->in_wire[i]->reg & wires->in_wire[i]->mask) ? (1 << i) : 0;
		wires->morituri |= wire_value;
	}

	wires->cache = wires->morituri;
	printf("[%s] morituri=%x\n", module->name, wires->morituri);

	return 1;
}

int wires_tick(struct bomb * bomb, struct module * module) {
	struct wires * wires = (struct wires *)module;

	for (uint8_t i=0; i<6; ++i) {
		uint8_t wire_mask = 1 << i;
		uint8_t wire_value = (*wires->in_wire[i]->reg & wires->in_wire[i]->mask) ? (1 << i) : 0;
		if ((wires->cache & wire_mask) ^ wire_value) { //a wire has changed!
			printf("[%s] wires=%x->", wires->cache);
			wires->cache = (wires->cache & ~wire_mask) | wire_value;
			printf("%s\n", wires->cache);

			if (!wire_value) { //wire was removed
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
			else {
				printf("\t(added)\n");
			}
		}
	}

	return 0;
}
