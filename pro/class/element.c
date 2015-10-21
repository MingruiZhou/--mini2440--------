#include "element.h"
#include <stdio.h>

unsigned char *picture[ELEMENT_NUM + 1] = {
	NULL,
	element1,
	element2,
	element3,
	element4,
	element5,
	element6,
	element7,
	element8,
	element9,
	element10,
	element11,
	element12
};

/*****************************************************************
 * 函数名称：initElement
 * 描述说明：初始化矩阵元素值
 * 输入参数：e为矩阵元素指针,picId为初始化值
 * 输出参数：无
*****************************************************************/
void initElement(Element_t *e, int8 picId)
{
	e->m_picId = picId;
}

/*****************************************************************
 * 函数名称：showElement
 * 描述说明：显示连连看图元
 * 输入参数：e:矩阵元素指针,row:显示的行,clumn:显示的列,matY:显示图标矩阵的起始位置
 * 输出参数：无
*****************************************************************/
void showElement(Element_t *e, int row, int clumn, uint16 matY)
{
	int x = 0, y = 0;

	if(row >= 1 && row < MAT_ROW - 1 && clumn >= 1 && clumn < MAT_CLUMN -1 && e->m_picId != 0){
		x = clumn * ELEMENT_WIDTH + (ELEMENT_WIDTH - PIC_WIDTH) / 2;
		y = row * ELEMENT_WIDTH + (ELEMENT_WIDTH - PIC_WIDTH) / 2 + matY;

		Paint_Bmp(x, y, PIC_WIDTH, PIC_WIDTH, picture[e->m_picId]);
	}
}

