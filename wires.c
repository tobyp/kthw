#include "wires.h"

#include "util.h"

enum {
	WI_NONE,
	WI_WHITE,
	WI_YELLOW,
	WI_RED,
	WI_BLUE,
	WI_BLACK,
};

/* resistances of the wires (between ADC pin and the shift register output diodes),
and the voltage divider resistor (between ADC pin and ground), in Ohms.
Use something >= 1kOhm for the voltage divider (limits the current to <= 3.3mV),
and values in the range [0.1*voltdiv, 10*voltdiv] for the wires (even spacing if possible).*/
#define R_VOLTDIV 1000
#define R_WHITE 100
#define R_YELLOW 510
#define R_RED 1000
#define R_BLUE 4700
#define R_BLACK 10000

char const* color_names[] = {"<none>", "WHITE", "YELLOW", "RED", "BLUE", "BLACK"};

#define VOLTDIV(x, y) ((y) * 3096 / ((x) + (y)))  //the value we'd expect at the ADC pin with X Ohms against VCC and Y Ohms against GND
#define MID(x, y) ((x) + (y)) / 2

#define ADC_WHITE VOLTDIV(R_WHITE,R_VOLTDIV)
#define ADC_YELLOW VOLTDIV(R_YELLOW,R_VOLTDIV)
#define ADC_RED VOLTDIV(R_RED,R_VOLTDIV)
#define ADC_BLUE VOLTDIV(R_BLUE,R_VOLTDIV)
#define ADC_BLACK VOLTDIV(R_BLACK,R_VOLTDIV)

static struct color_range {
	uint8_t color;
	uint16_t upper;
} color_ranges[] = {
	{WI_NONE, MID(0, ADC_BLACK)},
	{WI_BLACK, MID(ADC_BLACK, ADC_BLUE)},
	{WI_BLUE, MID(ADC_BLUE, ADC_RED)},
	{WI_RED, MID(ADC_RED, ADC_YELLOW)},
	{WI_YELLOW, MID(ADC_YELLOW, ADC_WHITE)},
	{WI_WHITE, MID(ADC_WHITE, 3096)},
};

static uint8_t adc_to_color(uint16_t adc) {
	for (size_t i=0; i<sizeof(color_ranges)/sizeof(struct color_range); ++i) {
		if (adc < color_ranges[i].upper) return color_ranges[i].color;
	}
	return WI_NONE;
}

static uint8_t wires_count_color(uint8_t * wires, uint8_t color) {
	uint8_t count = 0;
	for (size_t i=0; i<8; ++i) {
		if (wires[i] == color) count++;
	}
	return count;
}

static uint8_t wires_index_nth_color(uint8_t * wires, int8_t n, uint8_t color) {
	//get array index for the nth wire that has specific color (top wire=0)
	//negative n counts from end (bottom wire=-1)
	if (n < 0) {
		for (int8_t i=7; i >= 0; i--) {
			if (wires[i] == color) n++;
			if (n == 0) return i;
		}
	}
	else {
		n += 1; //for the 0 offset
		for (int8_t i=0; i < 8; i++) {
			if (wires[i] == color) n--;
			if (n == 0) return i;
		}
	}
	return 0xff;
}

static uint8_t wires_index_nth(uint8_t * wires, int8_t n) {
	//get array index for the nth wire (top wire=0)
	//negative n counts from end (bottom wire=-1)
	if (n < 0) {
		for (int8_t i=7; i >= 0; i--) {
			if (wires[i] != WI_NONE) n++;
			if (n == 0) return i;
		}
	}
	else {
		n += 1; //for the 0 offset
		for (int8_t i=0; i < 8; i++) {
			if (wires[i] != WI_NONE) n--;
			if (n == 0) return i;
		}
	}
	return 0xff;
}

static uint8_t wire_to_cut(struct bomb * bomb, struct wires * wires) {
	//return index of wire to cut
	uint8_t cut = 0xff;
	uint8_t i_first = wires_index_nth(wires->wires, 0);
	uint8_t i_second = wires_index_nth(wires->wires, 1);
	uint8_t i_fourth = wires_index_nth(wires->wires, 3);
	uint8_t i_last = wires_index_nth(wires->wires, -1);
	uint8_t col_last = wires->wires[i_last];
	uint8_t num_yellow = wires_count_color(wires->wires, WI_YELLOW);
	uint8_t num_red = wires_count_color(wires->wires, WI_RED);
	uint8_t num_blue = wires_count_color(wires->wires, WI_BLUE);
	uint8_t ser_odd = !(bomb->flags & FL_SER_EVEN);
	if (wires->count == 3) {
		uint8_t i_last_blue = wires_index_nth_color(wires->wires, -1, WI_BLUE);
		if (num_red == 0) cut = i_second;
		else if (col_last == WI_WHITE) cut = i_last;
		else if (num_blue > 1) cut = i_last_blue;
		else cut = i_last;
	}
	else if (wires->count == 4) {
		uint8_t i_last_red = wires_index_nth_color(wires->wires, -1, WI_RED);
		if (num_red > 1 && ser_odd) cut = i_last_red;
		else if (col_last == WI_YELLOW && num_red == 0) cut = i_first;
		else if (num_blue == 1) cut = i_first;
		else if (num_yellow > 1) cut = i_last;
		else cut = i_second;
	}
	else if (wires->count == 5) {
		uint8_t num_black = wires_count_color(wires->wires, WI_BLACK);
		if (col_last == WI_BLACK && ser_odd) cut = i_fourth;
		else if (num_red == 1 && num_yellow > 1) cut = i_first;
		else if (num_black == 0) cut = i_second;
		else cut = i_first;
	}
	else if (wires->count == 6) {
		uint8_t i_third = wires_index_nth(wires->wires, 2);
		uint8_t num_white = wires_count_color(wires->wires, WI_WHITE);
		if (num_yellow == 0 && ser_odd) cut = i_third;
		else if (num_yellow == 1 && num_white > 1) cut = i_fourth;
		else if (num_red == 0) cut = i_last;
		else cut = i_fourth;
	}

	if (cut == 0xff) {
		printf("[%s] WARNING: module starts out completed\n", wires->module.name);
		wires->module.flags |= MF_COMPLETE;
	}
	else {
		printf("[%s] cut wire %d\n", wires->module.name, cut);
	}
	return cut;
}

void wires_prepare_tick(struct bomb * bomb, struct module * module) {
	struct wires * wires = (struct wires *)module;

	if (wires->ticks != 0) {
		if (wires->adc->value == 0xffff) { //ADC hasn't refreshed yet
			return;
		}
		/* calculate the index of the wire we started polling last tick. -1 because tick 0 is not polling anything yet. */
		uint8_t wire_index = (wires->ticks - 1) % 8;
		printf("[XXX] %d = %d\n", wire_index, wires->adc->value);
		wires->wires[wire_index] = adc_to_color(wires->adc->value);
	}

	wires->ticks = (wires->ticks + 1);
	uint8_t wire_index = (wires->ticks - 1) % 8;
	uint8_t wire_mask = 1 << wire_index;
	wires->shreg->value = wire_mask;
	wires->adc->value = 0xffff;

	if (wires->ticks == 9) {
		wires->ticks = 0;

		printf("[%s] wires=[", module->name);
		for (size_t i=0; i<8; ++i) {
			if (wires->wires[i] != WI_NONE) {
				printf("%s ", color_names[wires->wires[i]]);
				wires->count++;
			}
		}
		printf("%s]\n", wires->count ? "\b" : "");
		module->flags |= MF_READY;
		wires->morituri = wire_to_cut(bomb, wires);
	}
}

void wires_tick(struct bomb * bomb, struct module * module) {
	struct wires * wires = (struct wires *)module;

	if (wires->adc->value == 0xffff) { //ADC hasn't refreshed yet
		return;
	}

	uint8_t wire_index = wires->ticks % 8;
	uint8_t wire_color = adc_to_color(wires->adc->value);

	if (wire_color != wires->wires[wire_index]) { //a wire has changed!
		printf("[%s] wire %d %s->%s\n", module->name, wire_index, color_names[wires->wires[wire_index]], color_names[wire_color]);
		wires->wires[wire_index] = wire_color;

		if (wire_color == WI_NONE && wire_index == wires->morituri) {
			module->flags |= MF_COMPLETE;
			wires->shreg->value = 0;
			return;
		}
		else {
			strike(bomb, module);
		}
	}

	wires->ticks = (wires->ticks + 1) % 8;
	wire_index = wires->ticks % 8;
	uint8_t wire_mask = 1 << wire_index;
	wires->shreg->value = wire_mask;
	wires->adc->value = 0xffff;
}
