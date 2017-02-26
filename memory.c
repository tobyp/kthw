#include "memory.h"

enum {
	MEM_POS,
	MEM_LBL,
	MEM_SAME_POS,
	MEM_SAME_LBL,
};

static struct stage_rule {
	struct stage_num_rule {
		uint8_t rule; uint8_t n;
	} display_values[4];
} rules[] = {
	{{{MEM_POS, 1}, {MEM_POS, 1}, {MEM_POS, 2}, {MEM_POS, 3},}},
	{{{MEM_LBL, 3}, {MEM_SAME_POS, 0}, {MEM_POS, 0}, {MEM_SAME_POS, 0},}},
	{{{MEM_SAME_LBL, 1}, {MEM_SAME_LBL, 0}, {MEM_POS, 2}, {MEM_LBL, 3},}},
	{{{MEM_SAME_POS, 0}, {MEM_POS, 0}, {MEM_SAME_POS, 1}, {MEM_SAME_POS, 1},}},
	{{{MEM_SAME_LBL, 0}, {MEM_SAME_LBL, 1}, {MEM_SAME_LBL, 3}, {MEM_SAME_LBL, 2},}},
};

static inline uint8_t expected_lbl(struct memory * memory) {
	struct stage_num_rule * rule = &rules[memory->stage].display_values[memory->display];
	switch (rule->rule) {
		case MEM_POS: return memory->buttons[rule->n];
		case MEM_LBL: return rule->n;
		case MEM_SAME_POS: return memory->buttons[memory->pos_hist[rule->n]];
		case MEM_SAME_LBL:
		default: return memory->lbl_hist[rule->n];
	}
}

static inline void populate(struct memory * memory) {
	memory->display = rnd() % 4;
	memory->buttons[0] = 0;
	memory->buttons[1] = 1;
	memory->buttons[2] = 2;
	memory->buttons[3] = 3;
	//shuffle
	print("memory: \""); print_uint(memory->display + 1);
	print("\" ["); print_uint(memory->buttons[0] + 1);
	print(" "); print_uint(memory->buttons[1] + 1);
	print(" "); print_uint(memory->buttons[2] + 1);
	print(" "); print_uint(memory->buttons[3] + 1);
	print("]\n");
}

int memory_prepare_tick(struct bomb * bomb, struct module * module) {
	struct memory * memory = (struct memory *)module;

	memory->ticks = 0;
	memory->stage = 0;
	populate(memory);

	return 1;
}

int memory_tick(struct bomb * bomb, struct module * module) {
	struct memory * memory = (struct memory *)module;

	memory->sr_display->value = sevenseg_digits[memory->display + 1];
	memory->sr_btn_lbls[0]->value = sevenseg_digits[memory->buttons[0] + 1];
	memory->sr_btn_lbls[1]->value = sevenseg_digits[memory->buttons[1] + 1];
	memory->sr_btn_lbls[2]->value = sevenseg_digits[memory->buttons[2] + 1];
	memory->sr_btn_lbls[3]->value = sevenseg_digits[memory->buttons[3] + 1];

	uint32_t poll_index = memory->ticks;
	uint8_t poll_mask = 1 << poll_index;
	uint8_t poll_value = (*memory->in_btn->reg & memory->in_btn->mask) ? poll_mask : 0;
	if ((memory->btn_cache & poll_mask) ^ poll_value) { //a wire has changed!
		memory->btn_cache = (memory->btn_cache & ~poll_mask) | poll_value;
		if (poll_value) { //button is now pushed
			if (poll_index == expected_lbl(memory)) {
				memory->lbl_hist[memory->stage] = memory->buttons[poll_index];
				memory->pos_hist[memory->stage] = poll_index;
				memory->stage++;
				if (memory->stage == 5) return 1;
			}
			else {
				strike(bomb);
				memory->stage = 0;
			}
			populate(memory);
		}
	}

	memory->ticks = (memory->ticks + 1) % 4;
	poll_index = memory->ticks;
	poll_mask = 1 << poll_index;
	memory->sr_btn->value = poll_mask;

	memory->sr_stage->value = (1 << (memory->stage + 1)) - 1;

	return 0;
}

void memory_reset(struct bomb * bomb, struct module * module) {
	struct memory * memory = (struct memory *)module;

	memory->sr_display->value = 0;
	memory->sr_stage->value = 0;
	memory->sr_btn->value = 0;
	memory->sr_btn_lbls[0]->value = 0;
	memory->sr_btn_lbls[1]->value = 0;
	memory->sr_btn_lbls[2]->value = 0;
	memory->sr_btn_lbls[3]->value = 0;
}
