#include "myUi.h"

/*****************************************************************
 * 函数名称：initMenuPic
 * 描述说明：初始化图片
 * 输入参数：p_menuPic:菜单指针, x:起始点x坐标, y:起始点y坐标, w:图片的宽度, h:图片的高度,  p_bmp:图片指针
 * 输出参数：无
*****************************************************************/
void initMenuPic(menuPic_t *p_menuPic, int16 x, int16 y, int16 w, int16 h,  unsigned char *p_bmp)
{
	p_menuPic->x = x;
	p_menuPic->y = y;
	p_menuPic->w= w;
	p_menuPic->h = h;
	p_menuPic->bmp = p_bmp;	
}

/*****************************************************************
 * 函数名称：initStartUi
 * 描述说明：初始化开始界面的菜单
 * 输入参数：p_ui:要显示ui的指针
 * 输出参数：无
*****************************************************************/
void initStartUi(ui_t *p_ui)
{
	p_ui->backColor = 0xffff;
	p_ui->menuCount = 4;

	initMenuPic(&p_ui->title, 0, 0, 240, 40, tit_start);
	
	initMenuPic(&p_ui->menuPic[0], 50, 50, 150, 40, menu_block1);
	initMenuPic(&p_ui->menuPic[1], 50, 100, 150, 40 , menu_block2);
	initMenuPic(&p_ui->menuPic[2], 50, 150, 150, 40, menu_block3);
	initMenuPic(&p_ui->menuPic[3], 50, 200, 150, 40, menu_exit);
}

/*****************************************************************
 * 函数名称：initGameUi
 * 描述说明：初始化连连看游戏界面
 * 输入参数：p_ui:要显示ui的指针
 * 输出参数：无
*****************************************************************/
void initGameUi(ui_t *p_ui)
{
	p_ui->backColor = 0xffff;
	p_ui->menuCount = 2;

	initMenuPic(&p_ui->title, 0, 0, 240, 30, tit_lian);
	
	initMenuPic(&p_ui->menuPic[0], 5, 285, 80, 30, menu_restart);
	initMenuPic(&p_ui->menuPic[1], 155, 285, 80, 30 , menu_g_back);
}

/*****************************************************************
 * 函数名称：initNextUi
 * 描述说明：初始化下一关界面
 * 输入参数：p_ui:要显示ui的指针
 * 输出参数：无
*****************************************************************/
void initNextUi(ui_t *p_ui)
{
	p_ui->backColor = 0xffff;
	p_ui->menuCount = 2;

	initMenuPic(&p_ui->title, 0, 0, 240, 40, tit_seccess);
	
	initMenuPic(&p_ui->menuPic[0], 50, 80, 150, 40, menu_back);
	initMenuPic(&p_ui->menuPic[1], 50, 160, 150, 40 , menu_next);
}

/*****************************************************************
 * 函数名称：initTimeOutUi
 * 描述说明：初始化超时界面的菜单
 * 输入参数：p_ui:要显示ui的指针
 * 输出参数：无
*****************************************************************/
void initTimeOutUi(ui_t *p_ui)
{
	p_ui->backColor = 0xffff;
	p_ui->menuCount = 2;

	initMenuPic(&p_ui->title, 0, 0, 240, 60, tit_timeOut);
	
	initMenuPic(&p_ui->menuPic[0], 50, 100, 150, 40, menu_back);
	initMenuPic(&p_ui->menuPic[1], 50, 180, 150, 40 , menu_again);
}

/*****************************************************************
 * 函数名称：initNoConnectUi
 * 描述说明：初始化死局界面
 * 输入参数：p_ui:要显示ui的指针
 * 输出参数：无
*****************************************************************/
void initNoConnectUi(ui_t *p_ui)
{
	p_ui->backColor = 0xffff;
	p_ui->menuCount = 2;

	initMenuPic(&p_ui->title, 0, 0, 240, 60, tit_noConnect);
	
	initMenuPic(&p_ui->menuPic[0], 50, 100, 150, 40, menu_back);
	initMenuPic(&p_ui->menuPic[1], 50, 180, 150, 40 , menu_again);
}

/*****************************************************************
 * 函数名称：initWinUi
 * 描述说明：初始化游戏成功界面
 * 输入参数：p_ui:要显示ui的指针
 * 输出参数：无
*****************************************************************/
void initWinUi(ui_t *p_ui)
{
	p_ui->backColor = 0xffff;
	p_ui->menuCount = 1;

	initMenuPic(&p_ui->title, 0, 0, 240, 90, tit_win);
	
	initMenuPic(&p_ui->menuPic[0], 50, 180, 150, 40, menu_ok);
}

/*****************************************************************
 * 函数名称：initEndUi
 * 描述说明：初始化结束界面
 * 输入参数：p_ui:要显示ui的指针
 * 输出参数：无
*****************************************************************/
void initEndUi(ui_t *p_ui)
{
	p_ui->backColor = 0xffff;
	p_ui->menuCount = 2;
	
	initMenuPic(&p_ui->title, 0, 0, 240, 40, tit_exitGame);
	
	initMenuPic(&p_ui->menuPic[0], 50, 80, 150, 40, menu_exit);
	initMenuPic(&p_ui->menuPic[1], 50, 160, 150, 40 , menu_back);
}


