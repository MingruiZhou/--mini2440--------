#ifndef UI_H
#define UI_H

#include "share.h"

typedef struct MENU_PIC{
	int16 x;
	int16 y;
	int16 w;
	int16 h;
	unsigned char *bmp;
}menuPic_t;

typedef struct UI{
	uint16 backColor;
	int16 menuCount;
	menuPic_t title;
	menuPic_t menuPic[4];
}ui_t;

void showWin(ui_t *p_ui);

int getMenu(ui_t *p_ui, struct LcdDot *p_touchXY);

int execWin(ui_t *p_ui);

#endif
