#include <stdio.h>
#include "ui.h"
#include "LCD.h"


/*****************************************************************
 * 函数名称：showWin
 * 描述说明：显示界面
 * 输入参数：p_ui:要显示ui的指针
 * 输出参数：无
*****************************************************************/
void showWin(ui_t *p_ui)
{
	int i = 0;
	
	Paint_Bmp(0, 0, 240, 319, white); //这里不能用320,原因不明
	Paint_Bmp(p_ui->title.x, p_ui->title.y, p_ui->title.w, p_ui->title.h, p_ui->title.bmp);

	//显示每个菜单
	for(i = 0; i < p_ui->menuCount; i ++){
		Paint_Bmp(p_ui->menuPic[i].x, p_ui->menuPic[i].y, p_ui->menuPic[i].w, p_ui->menuPic[i].h, p_ui->menuPic[i].bmp);
	}
}

/*****************************************************************
 * 函数名称：showMenuBoard
 * 描述说明：显示菜单的边框
 * 输入参数：p_menuPic:菜单指针,color:颜色值
 * 输出参数：无
*****************************************************************/
void showMenuBoard(menuPic_t *p_menuPic, uint16 color)
{
	
	uint16 x1, y1;
	uint16 x2, y2;

	x1 = p_menuPic->x - 1;
	y1 = p_menuPic->y - 1;

	x2 = x1 + p_menuPic->w + 1;
	y2 = y1 + p_menuPic->h + 1;
	
	GUI_DrawRect(x1, y1, x2, y2, color);
}

/*****************************************************************
 * 函数名称：getMenu
 * 描述说明：判断得到所选择的菜单
 * 输入参数：p_ui:界面指针,p_touchXY:坐标
 * 输出参数：0:没有点击任何菜单,其他值:点击的菜单值
*****************************************************************/
int getMenu(ui_t *p_ui, struct LcdDot *p_touchXY)
{
	int i = 0;
	uint16 x = 0, y = 0;
	
	x = p_touchXY->x;
	y = p_touchXY->y;
	for(i = 0; i < p_ui->menuCount; i ++){
		if(x >= p_ui->menuPic[i].x &&
			x <= p_ui->menuPic[i].x + p_ui->menuPic[i].w &&
			y >= p_ui->menuPic[i].y &&
			y <= p_ui->menuPic[i].y + p_ui->menuPic[i].h){
			showMenuBoard(&p_ui->menuPic[i], BOARD_COLOR);
			gameDelay(1000);
			return i + 1;
		}
	}

	return 0;
}

/*****************************************************************
 * 函数名称：execWin
 * 描述说明：执行界面
 * 输入参数：p_ui:界面指针
 * 输出参数：返回点击菜单的值
*****************************************************************/
int execWin(ui_t *p_ui)
{
	int ret = 0;
	struct LcdDot touchXY;
	
	showWin(p_ui);

#if 0
	do{
		while(GetTouch(&touchXY) == 0);
		ret = getMenu(p_ui, &touchXY);
	}while(ret == 0);
#else
	while(1){
		while(GetTouch(&touchXY) == 0);
		ret = getMenu(p_ui, &touchXY);
		if(ret > 0){
			return ret;
		}
	}
#endif

	return ret;
}

