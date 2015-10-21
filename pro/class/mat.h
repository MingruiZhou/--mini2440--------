#ifndef MAT_H
#define MAT_H

#include "element.h"
#include "share.h"

typedef struct MAT{
	Element_t mat[MAT_ROW][MAT_CLUMN];
	uint16 m_matY;
}mat_t;

void initMat(mat_t *p_mat, uint16 matY, int blockNum);

void showMat(mat_t *p_mat);

int getLocation(mat_t *p_mat, struct LcdDot *p_touchXY, location_t *p_curLoc);

int isSuccess(mat_t *p_mat);

void showBoard(mat_t *p_mat, location_t *pLocation, uint16 color );

void clearPic(mat_t *p_mat, location_t *p_loc);

void printfMat(mat_t *p_mat);

void clearPicShow(mat_t *p_mat, location_t *pLocation, uint16 color );

#endif
