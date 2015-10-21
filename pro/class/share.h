#ifndef SHARE_H
#define SHARE_H

#include "sys.h"
#include "adc.h"
#include "gui.h"

#include "elementPic.h"
#include "menuPic.h"
#include "titlePic.h"


#define BLOCK_NUM 3

#define ELEMENT_NUM 12

#define MAT_ROW 10
#define MAT_CLUMN 10

#define ELEMENT_WIDTH 24
#define PIC_WIDTH 20

#define BOARD_COLOR 0xf800
#define LINK_LINE_COLOR 0xf800
#define LINK_LINE_SIZE 2


typedef struct LOCATION{
	int row;
	int clumn;
}location_t;

extern unsigned long LoopVal;
extern int restTime;
extern int noConnectTime;
extern int gameExeFlag;

void gameDelay(int count);

void showTime(int restTime);

void showTimeOut(void);

void myTime0Handle(void);

#endif
