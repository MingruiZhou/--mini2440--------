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
 * �������ƣ�initElement
 * ����˵������ʼ������Ԫ��ֵ
 * ���������eΪ����Ԫ��ָ��,picIdΪ��ʼ��ֵ
 * �����������
*****************************************************************/
void initElement(Element_t *e, int8 picId)
{
	e->m_picId = picId;
}

/*****************************************************************
 * �������ƣ�showElement
 * ����˵������ʾ������ͼԪ
 * ���������e:����Ԫ��ָ��,row:��ʾ����,clumn:��ʾ����,matY:��ʾͼ��������ʼλ��
 * �����������
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

