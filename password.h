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
	char letters[5][6];
	uint8_t selections[5];
	uint8_t pos;

	uint8_t ticks;
	uint8_t cache;

	struct lcd_cache { uint8_t mode; uint8_t cmd; } lcd_cache[6];
};

void password_prepare_tick(struct bomb * bomb, struct module * module);
void password_tick(struct bomb * bomb, struct module * module);
void password_reset(struct bomb * bomb, struct module * module);

#define PASSWORD_MOD_INIT {"password", 0, &password_prepare_tick, &password_tick, &password_reset, NULL}

#endif