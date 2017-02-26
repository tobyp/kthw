#include "wires.h"

#include "util.h"

int wires_prepare_tick(struct bomb * bomb, struct module * module) {
	struct wires * wires = (struct wires *)module;

	for (uint8_t i=0; i<6; ++i) {
		uint8_t wire_value = (*wires->in_wire[i]->reg & wires->in_wire[i]->mask) ? (1 << i) : 0;
		wires->wires_to_cut |= wire_value;
	}

	wires->wire_cache = wires->wires_to_cut;
	print("wires init: tocut="); print_uint_hex(wires->wires_to_cut); print("\n");

	return 1;
}

int wires_tick(struct bomb * bomb, struct module * module) {
	struct wires * wires = (struct wires *)module;

	for (uint8_t i=0; i<6; ++i) {
		uint8_t wire_mask = 1 << i;
		uint8_t wire_value = (*wires->in_wire[i]->reg & wires->in_wire[i]->mask) ? (1 << i) : 0;
		if ((wires->wire_cache & wire_mask) ^ wire_value) { //a wire has changed!
			print("wires: "); print_uint_hex(wire_mask); print("="); print_uint_hex(wire_value); print(" wires:"); print_uint_hex(wires->wire_cache); print("->");
			wires->wire_cache = (wires->wire_cache & ~wire_mask) | wire_value;
			print_uint_hex(wires->wire_cache); print("\n");

			if (!wire_value) { //wire was removed
				if (wire_mask & wires->wires_to_cut) { //a correct one
					print("\t(removed correctly)\n");
					if (!(wires->wire_cache & wires->wires_to_cut)) { //no wire remains to be cut
						return 1;
					}
				}
				else {
					strike(bomb);
				}
			}
			else {
				print("\t(added)\n");
			}
		}
	}

	return 0;
}
