#include "password.h"

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

char impossibles[5][15] = {
	"DIJKMQUVXYZ",
	"CDJKNQSUWXYZ",
	"BCDFJKMNPQSWXYZ",
	"BFJKMPQVWXYZ",
	"ABCFIJMOPQSTVXZ",
};

//letters[pos][offset]

static void sort_char(char * array, size_t length) {
	for (size_t i=1; i<length; ++i) {
		for (size_t j=i; j<length; ++j) {
			if (array[i-1] > array[i]) {
				char tmp = array[i-1];
				array[i-1] = array[i];
				array[i] = tmp;
			}
		}
	}
}

static void populate_cylinders(struct password * password) {
	uint8_t possibilities[sizeof(words)/sizeof(struct word)];

	password->letters[0][0] = password->word->chars[0];
	password->letters[1][0] = password->word->chars[1];
	password->letters[2][0] = password->word->chars[2];
	password->letters[3][0] = password->word->chars[3];
	password->letters[4][0] = password->word->chars[4];

	for (uint8_t i=0; i<5; ++i) {
		password->letters[i][1] = rnd() % 26 + 'A';
		password->letters[i][2] = rnd() % 26 + 'A';
		password->letters[i][3] = rnd() % 26 + 'A';
		password->letters[i][4] = rnd() % 26 + 'A';
		password->letters[i][5] = rnd() % 26 + 'A';
		sort_char(password->letters[i], 6);
	}

	for (uint8_t j=0; j<sizeof(possibilities); ++j) {
		
	}
}

int password_prepare_tick(struct bomb * bomb, struct module * module) {
	struct password * password = (struct password *)module;
	switch (password->ticks) {
	//init
	case 0:
		password->word = &words[rnd() % (sizeof(words)/sizeof(struct word))];
		printf("[%s] word=\"%s\"\n", module->name, password->word->chars);

		password->cache = (*password->in_submit->reg & password->in_submit->mask ? 0x80 : 0) |
			(*password->in_updown[1]->reg & password->in_updown[1]->mask ? 0x2 : 0) |
			(*password->in_updown[0]->reg & password->in_updown[0]->mask ? 0x1 : 0);

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
		return 1;
	}
	password->ticks++;
	return 0;
}

int password_tick(struct bomb * bomb, struct module * module) {
	struct password * password = (struct password *)module;

	uint16_t pos = password->adc_position->value * 5 / 4096;
	uint8_t btns = (*password->in_submit->reg & password->in_submit->mask ? 0x80 : 0) |
		(*password->in_updown[1]->reg & password->in_updown[1]->mask ? 0x2 : 0) |
		(*password->in_updown[0]->reg & password->in_updown[0]->mask ? 0x1 : 0);

	//Submit
	if ((btns & 0x80) != (password->cache & 0x80) && (btns & 0x80)) { //button edge!
		for (uint8_t i=0; i<6; ++i) {
			if (password->letters[i][password->selections[i]] != password->word->chars[i]) {
				strike(bomb);
				return 0;
			}
		}
		return 1;
	}

	if (pos != password->pos) {
		password->lcd_cache[0].mode = LCD_CMD;
		password->lcd_cache[0].cmd = LCD_CMD_CURSOR(1, 1 + 3*password->pos);
		password->lcd_cache[1].mode = LCD_DATA;
		password->lcd_cache[1].cmd = ' ';
		password->lcd_cache[2].mode = LCD_CMD;
		password->lcd_cache[2].cmd = LCD_CMD_CURSOR(1, 1 + 3*pos);
		password->lcd_cache[3].mode = LCD_DATA;
		password->lcd_cache[3].cmd = '^';
	}
	else {
		uint8_t sel = password->selections[pos];
		if ((btns & 0x1) != (password->cache & 0x1) && (btns & 0x1)) {
			sel = (sel + 5) % 6; //equivalent to -1 without the underflow (which should be harmless but makes me queasy)
		}
		if ((btns & 0x2) != (password->cache & 0x2) && (btns & 0x2)) {
			sel = (sel + 1) % 6;
		}
		if (sel != password->selections[pos]) {
			password->selections[pos] = sel;
			password->lcd_cache[4].mode = LCD_CMD;
			password->lcd_cache[4].cmd = LCD_CMD_CURSOR(0, 1 + 3*pos);
			password->lcd_cache[5].mode = LCD_DATA;
			password->lcd_cache[5].cmd = password->letters[pos][sel];
		}
	}

	password->pos = pos;
	password->cache = btns;

	for (uint8_t i=0; i<6; ++i) {
		if (password->lcd_cache[i].mode != LCD_NONE) {
			password->lcd->mode = password->lcd_cache[i].mode;
			password->lcd->cmd = password->lcd_cache[i].cmd;
			password->lcd_cache[i].mode = LCD_NONE;
			break;
		}
	}

	return 0;
}

void password_reset(struct bomb * bomb, struct module * module) {
	struct password * password = (struct password *)module;

	password->lcd->mode = LCD_CMD;
	password->lcd->cmd = 0x01;
}