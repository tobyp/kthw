/* KTHW - Hardware Clone of Keep Talking and Nobody Explodes
Copyright (C) 2017 Toby P., Thomas H.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef PASSWORD_H_
#define PASSWORD_H_

#include <stdint.h>

#include "bomb.h"
#include "util.h"

struct word {
	char chars[6];
};

struct password {
	struct module module;
	struct gpio * in;
	struct shreg * ser;
	struct lcd * lcd;

	struct word * word;
	char letters[5][6];  // 5 column cylinders with 6 letters each
	uint8_t selections[5];  // currently selected index for each column
	uint8_t pos;  // currently focused column

	uint8_t ticks;
	uint8_t cache;

	struct lcd_cache { uint8_t mode; uint8_t cmd; } lcd_cache[6];
};

void password_prepare_tick(struct bomb * bomb, struct module * module);
void password_tick(struct bomb * bomb, struct module * module);
void password_reset(struct bomb * bomb, struct module * module);

#define PASSWORD_MOD_INIT {"password", 0, &password_prepare_tick, &password_tick, &password_reset, NULL}

#endif