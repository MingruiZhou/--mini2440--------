#ifndef _GUI_H
#define _GUI_H

#include "sys.h"
#include "adc.h"

//����û�ѡ��Ĺ���ģ��
uint8 GetIcon(struct LcdDot *tmpXY);

//���ƴ�ֱֱ��
uint8 GUI_DrawVLine(uint16 Left,uint16 Top,uint16 Bottom,uint16 Color);

//����ˮƽֱ��
uint8 GUI_DrawHLine(uint16 Left,uint16 Top,uint16 Right,uint16 Color);

//���ƾ��ο�
uint8 GUI_DrawRect(uint16 X0, uint16 Y0, uint16 X1, uint16 Y1, uint16 Color);

//����ֱ��
uint8 GUI_DrawLine(uint16 X0,uint16 Y0,uint16 X1,uint16 Y1,uint16 Color);

//����ɫ������
void GUI_FillRect(uint16 X1, uint16 Y1, uint16 X2, uint16 Y2, uint16 Color);

//��ˮ�Ʋ���
void LED_Test(void);

//ƴ�����뷨
void PY_Test(void);

#endif
