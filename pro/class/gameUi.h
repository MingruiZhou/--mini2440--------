#ifndef GAMEUI_H
#define GAMEUI_H

#include "ui.h"
#include "element.h"
#include "mat.h"
#include "gameMng.h"

typedef struct GAME_Ui{
	uint16 m_matY;
	ui_t m_ui;
	mat_t m_mat;
	gameMng_t m_gameMng;
}gameUi_t;

int execGame(gameUi_t *p_gameUi, int blockNum);

#endif
