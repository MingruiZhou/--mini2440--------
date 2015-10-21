#include "myUi.h"

/*****************************************************************
 * �������ƣ�initMenuPic
 * ����˵������ʼ��ͼƬ
 * ���������p_menuPic:�˵�ָ��, x:��ʼ��x����, y:��ʼ��y����, w:ͼƬ�Ŀ��, h:ͼƬ�ĸ߶�,  p_bmp:ͼƬָ��
 * �����������
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
 * �������ƣ�initStartUi
 * ����˵������ʼ����ʼ����Ĳ˵�
 * ���������p_ui:Ҫ��ʾui��ָ��
 * �����������
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
 * �������ƣ�initGameUi
 * ����˵������ʼ����������Ϸ����
 * ���������p_ui:Ҫ��ʾui��ָ��
 * �����������
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
 * �������ƣ�initNextUi
 * ����˵������ʼ����һ�ؽ���
 * ���������p_ui:Ҫ��ʾui��ָ��
 * �����������
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
 * �������ƣ�initTimeOutUi
 * ����˵������ʼ����ʱ����Ĳ˵�
 * ���������p_ui:Ҫ��ʾui��ָ��
 * �����������
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
 * �������ƣ�initNoConnectUi
 * ����˵������ʼ�����ֽ���
 * ���������p_ui:Ҫ��ʾui��ָ��
 * �����������
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
 * �������ƣ�initWinUi
 * ����˵������ʼ����Ϸ�ɹ�����
 * ���������p_ui:Ҫ��ʾui��ָ��
 * �����������
*****************************************************************/
void initWinUi(ui_t *p_ui)
{
	p_ui->backColor = 0xffff;
	p_ui->menuCount = 1;

	initMenuPic(&p_ui->title, 0, 0, 240, 90, tit_win);
	
	initMenuPic(&p_ui->menuPic[0], 50, 180, 150, 40, menu_ok);
}

/*****************************************************************
 * �������ƣ�initEndUi
 * ����˵������ʼ����������
 * ���������p_ui:Ҫ��ʾui��ָ��
 * �����������
*****************************************************************/
void initEndUi(ui_t *p_ui)
{
	p_ui->backColor = 0xffff;
	p_ui->menuCount = 2;
	
	initMenuPic(&p_ui->title, 0, 0, 240, 40, tit_exitGame);
	
	initMenuPic(&p_ui->menuPic[0], 50, 80, 150, 40, menu_exit);
	initMenuPic(&p_ui->menuPic[1], 50, 160, 150, 40 , menu_back);
}


