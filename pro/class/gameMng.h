#ifndef GAMEMNG_H
#define GMAEMNG_H

#include "share.h"
#include "Gui.h"
#include "mat.h"

typedef struct GAME_MNG{
	location_t locQueue[4];
	location_t curLoc;
	location_t firLoc;
	location_t secLoc;
	int m_locSize;
	int m_issec;
	int m_seccNum;
}gameMng_t;


void initGameMng(gameMng_t *p_gameMng);

void  drawLInkLine(gameMng_t *p_gameMng, mat_t *p_mat, uint16 color, int linkSize);

int isConnect(gameMng_t *p_gameMng, mat_t *p_mat);

int doGame(gameMng_t *p_gameMng, mat_t *p_mat, struct LcdDot *p_touchXY);

int seccess(gameMng_t *p_gamMng);

#endif
