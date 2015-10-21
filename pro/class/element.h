#ifndef ELEMENT_H
#define ELEMENT_H

#include "LCD.h"
#include "share.h"

typedef struct element{
	int8 m_picId;
}Element_t;

void initElement(Element_t *e, int8 picId);

void showElement(Element_t *e, int row, int clumn, uint16 matY);

#endif
