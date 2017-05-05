#include "password.h"

#include <stdlib.h>

struct word words[] = {
	{"ABOUT"},
	{"AFTER"},
	{"AGAIN"},
	{"BELOW"},
	{"COULD"},
	{"EVERY"},
	{"FIRST"},
	{"FOUND"},
	{"GREAT"},
	{"HOUSE"},
	{"LARGE"},
	{"LEARN"},
	{"NEVER"},
	{"OTHER"},
	{"PLACE"},
	{"PLANT"},
	{"POINT"},
	{"RIGHT"},
	{"SMALL"},
	{"SOUND"},
	{"SPELL"},
	{"STILL"},
	{"STUDY"},
	{"THEIR"},
	{"THERE"},
	{"THESE"},
	{"THING"},
	{"THINK"},
	{"THREE"},
	{"WATER"},
	{"WHERE"},
	{"WHICH"},
	{"WORLD"},
	{"WOULD"},
	{"WRITE"},
};

char impossibles[5][15] = { //some of these repeat the less exotic letters, to make them more likely, and also to match lengths of the arrays.
	"DIJKMQUVXYZDIKM",
	"CDJKNQSUWXYZNSD",
	"BCDFJKMNPQSWXYZ",
	"BFJKMPQVWXYZFMP",
	"ABCFIJMOPQSTVXZ",
};

#define BTN_RIGHT 0x1
#define BTN_LEFT 0x2
#define BTN_DOWN 0x4
#define BTN_UP 0x8
#define BTN_SUBMIT 0x10

static void populate_cylinders(struct password * password) {
	uint8_t possibilities[sizeof(words)/sizeof(struct word)];
	for (uint8_t i=0; i<sizeof(possibilities); ++i) {
		possibilities[i] = 0;
	}

	password->letters[0][0] = password->word->chars[0];
	password->letters[1][0] = password->word->chars[1];
	password->letters[2][0] = password->word->chars[2];
	password->letters[3][0] = password->word->chars[3];
	password->letters[4][0] = password->word->chars[4];

	uint32_t has_letter[5] = {
		1 << (password->letters[0][0] - 'A'),
		1 << (password->letters[1][0] - 'A'),
		1 << (password->letters[2][0] - 'A'),
		1 << (password->letters[3][0] - 'A'),
		1 << (password->letters[4][0] - 'A'),
	};

	//generate letters, and track which col has_letters, and which words are possible in which column
	for (uint8_t i=0; i<5; ++i) {
		for (uint8_t j=0; j<6; ++j) {
			if (j != 0) {
				uint8_t letter = rnd() % 26;
				while (has_letter[i] & (1 << letter)) {
					letter = (letter + 1) % 26;
				}
				password->letters[i][j] = letter + 'A';
				has_letter[i] |= (1 << letter);
			}
			for (uint8_t k=0; k<sizeof(possibilities); ++k) {
				if (words[k].chars[i] == password->letters[i][j]) {
					possibilities[k] |= (1 << i);
				}
			}
		}
	}

	//
	for (uint8_t k=0; k<sizeof(possibilities); ++k) {
		if (&words[k] == password->word) continue;
		if (possibilities[k] == 0x1f) { //this word is possible but shouldn't be--block it!
			uint8_t i = rnd() % 5; //block by changing a random position 
			while (password->word->chars[i] == words[k].chars[i]) { //do not exchange at a position where password == blockword
				i = (i + 1) % 5;
			}
			uint8_t choice = rnd() % sizeof(impossibles[i]); //change to a letter that never appears at this position.
			uint8_t j=0;
			while (words[k].chars[i] != password->letters[i][j]) { //find the letter that makes the blockword possible
				++j;
			}
			while (has_letter[i] & (1 << impossibles[i][choice])) { //do not replace with a duplicate
				choice = (choice + 1) % sizeof(impossibles[i]);
			}
			password->letters[i][j] = impossibles[i][choice];
		}
	}
}

void password_prepare_tick(struct bomb * bomb, struct module * module) {
	struct password * password = (struct password *)module;
	switch (password->ticks) {
	//init
	case 0:
		password->word = &words[rnd() % (sizeof(words)/sizeof(struct word))];
		printf("[%s] word=\"%s\"\n", module->name, password->word->chars);

		populate_cylinders(password);

		password->selections[0] = rnd() % 6;
		password->selections[1] = rnd() % 6;
		password->selections[2] = rnd() % 6;
		password->selections[3] = rnd() % 6;
		password->selections[4] = rnd() % 6;

		password->lcd->mode = LCD_CMD;
		password->lcd->cmd = 0x0c;
		break;
	case 1:
		password->lcd->mode = LCD_CMD;
		password->lcd->cmd = 0x38;
		break;
	case 2:
		password->lcd->mode = LCD_CMD;
		password->lcd->cmd = 0x06;
		break;
	case 3:
		password->lcd->mode = LCD_CMD;
		password->lcd->cmd = 0x01;
		break;
	//password
	case 4:
		password->lcd->mode = LCD_CMD;
		password->lcd->cmd = LCD_CMD_CURSOR(0, 1);
		break;
	case 5:
		password->lcd->mode = LCD_DATA;
		password->lcd->cmd = password->letters[0][password->selections[0]];
		break;
	case 6:
		password->lcd->mode = LCD_CMD;
		password->lcd->cmd = LCD_CMD_CURSOR(0, 4);
		break;
	case 7:
		password->lcd->mode = LCD_DATA;
		password->lcd->cmd = password->letters[1][password->selections[1]];
		break;
	case 8:
		password->lcd->mode = LCD_CMD;
		password->lcd->cmd = LCD_CMD_CURSOR(0, 7);
		break;
	case 9:
		password->lcd->mode = LCD_DATA;
		password->lcd->cmd = password->letters[2][password->selections[2]];
		break;
	case 10:
		password->lcd->mode = LCD_CMD;
		password->lcd->cmd = LCD_CMD_CURSOR(0, 10);
		break;
	case 11:
		password->lcd->mode = LCD_DATA;
		password->lcd->cmd = password->letters[3][password->selections[3]];
		break;
	case 12:
		password->lcd->mode = LCD_CMD;
		password->lcd->cmd = LCD_CMD_CURSOR(0, 13);
		break;
	case 13:
		password->lcd->mode = LCD_DATA;
		password->lcd->cmd = password->letters[4][password->selections[4]];
		break;
	case 14:
		password->lcd->mode = LCD_CMD;
		password->lcd->cmd = LCD_CMD_CURSOR(1, 1);
		break;
	case 15:
		password->lcd->mode = LCD_DATA;
		password->lcd->cmd = '^';
		break;
	default:
		password->ticks = 0;
		password->ser->value = 1;
		module->flags |= MF_READY;
		return;
	}
	password->ticks++;
}

void password_tick(struct bomb * bomb, struct module * module) {
	struct password * password = (struct password *)module;
	uint8_t pos = password->pos;
	uint8_t sel = password->selections[pos];

	uint32_t button_index = password->ticks;
	uint8_t button_mask = 1 << button_index;
	uint8_t button_value = gpio_get(password->in) ? button_mask : 0;
	if ((password->cache & button_mask) != button_value) {
		password->cache = (password->cache & ~button_mask) | button_value;
		if (button_value) {
			if (button_value == BTN_LEFT) {
				if (password->pos > 0) password->pos--;
			}
			else if (button_value == BTN_RIGHT) {
				if (password->pos < 4) password->pos++;
			}
			else if (button_value == BTN_UP) {
				sel = (sel + 5) % 6; //equivalent to -1 without the underflow (which should be harmless but makes me queasy)
			}
			else if (button_value == BTN_DOWN) {
				sel = (sel + 1) % 6;
			}
			else if (button_value == BTN_SUBMIT) {
				for (uint8_t i=0; i<6; ++i) {
					if (password->letters[i][password->selections[i]] != password->word->chars[i]) {
						strike(bomb, module);
						return;
					}
				}
				module->flags |= MF_COMPLETE;
				return;
			}
		}
	}

	if (password->pos != pos) {
		sel = password->selections[pos];
		password->lcd_cache[0].mode = LCD_CMD;
		password->lcd_cache[0].cmd = LCD_CMD_CURSOR(1, 1 + 3*pos);
		password->lcd_cache[1].mode = LCD_DATA;
		password->lcd_cache[1].cmd = ' ';
		password->lcd_cache[2].mode = LCD_CMD;
		password->lcd_cache[2].cmd = LCD_CMD_CURSOR(1, 1 + 3*password->pos);
		password->lcd_cache[3].mode = LCD_DATA;
		password->lcd_cache[3].cmd = '^';
	}

	if (password->selections[pos] != sel) {
		password->selections[pos] = sel;
		password->lcd_cache[4].mode = LCD_CMD;
		password->lcd_cache[4].cmd = LCD_CMD_CURSOR(0, 1 + 3*pos);
		password->lcd_cache[5].mode = LCD_DATA;
		password->lcd_cache[5].cmd = password->letters[pos][sel];
	}

	password->ticks = (password->ticks + 1) % 5;
	password->ser->value = 1 << password->ticks;

	//apply next LCD command
	for (uint8_t i=0; i<6; ++i) {
		if (password->lcd_cache[i].mode != LCD_NONE) {
			password->lcd->mode = password->lcd_cache[i].mode;
			password->lcd->cmd = password->lcd_cache[i].cmd;
			password->lcd_cache[i].mode = LCD_NONE;
			break;
		}
	}
}

void password_reset(struct bomb * bomb, struct module * module) {
	struct password * password = (struct password *)module;

	password->lcd->mode = LCD_CMD;
	password->lcd->cmd = 0x01;
}
