#ifndef _GUI_H
#define _GUI_H

#include "sys.h"
#include "adc.h"

//获得用户选择的功能模块
uint8 GetIcon(struct LcdDot *tmpXY);

//绘制垂直直线
uint8 GUI_DrawVLine(uint16 Left,uint16 Top,uint16 Bottom,uint16 Color);

//绘制水平直线
uint8 GUI_DrawHLine(uint16 Left,uint16 Top,uint16 Right,uint16 Color);

//绘制矩形框
uint8 GUI_DrawRect(uint16 X0, uint16 Y0, uint16 X1, uint16 Y1, uint16 Color);

//绘制直线
uint8 GUI_DrawLine(uint16 X0,uint16 Y0,uint16 X1,uint16 Y1,uint16 Color);

//用颜色填充矩形
void GUI_FillRect(uint16 X1, uint16 Y1, uint16 X2, uint16 Y2, uint16 Color);

//流水灯测试
void LED_Test(void);

//拼音输入法
void PY_Test(void);

#endif
