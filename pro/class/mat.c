#include "mat.h"
#include "sys.h"
#include <stdlib.h>
#include <stdio.h>

int8 Vmat[MAT_ROW][MAT_CLUMN] = 		 //如果这里全部初始化为零，则keil编译器会忽略初始化
{
	{0,0,0,0,0,0,0,0,0,0},
	{0,1,1,2,2,3,3,4,4,0},
	{0,1,1,2,2,3,3,4,4,0},
	{0,1,1,2,2,3,4,4,4,0},
	{0,1,1,2,2,4,3,4,4,0},
	{0,1,1,2,2,3,3,4,4,0},
	{0,1,1,2,2,3,3,4,4,0},
	{0,1,1,2,2,3,3,4,4,0},
	{0,1,1,2,2,3,3,4,4,0},
	{0,0,0,0,0,0,0,0,0,0}
};

static int PicRandNum[ELEMENT_NUM] = {0,0,0,0,0,0,0,0,0,0,0,0};

#if 1
/*****************************************************************
 * 函数名称：getRand
 * 描述说明：获取min到max的随机数
 * 输入参数：min:随机数最小值max:随机数最大值
 * 输出参数：无
*****************************************************************/
int getRand(int min, int max)
{

	int randNum;

	randNum = rand();
	randNum = randNum % (max - min + 1);

	return randNum + min;
}
#else

static char getRand(int min, int max)
{
    static unsigned int rnum = 0xabcd7381;

    rnum = ((rnum * 27) << 8) | (((rnum / 13) & 0xa5a7f196) + (rnum >> 13));

    return(rnum % (max - min + 1)) + min;
}

#endif

/*****************************************************************
 * 函数名称：getPicRandNum
 * 描述说明：得到各种图标的个数，保存到PicRandNum[ELEMENT_NUM] 中
 * 输入参数：p_mat:连连看逻辑矩阵类指针
 * 输出参数：无
*****************************************************************/
void getPicRandNum(mat_t *p_mat)
{
	int i, j;
	int index;

	for(i = 0; i < ELEMENT_NUM; i ++){
		PicRandNum[i] = 0;
	}

	for(i = 0; i < ELEMENT_NUM; i ++){
		Uart_Printf("picRandNum[%d]:%d\r\n", i, PicRandNum[i]);
	}


	for(i = 0; i < MAT_ROW; i ++){
		for(j = 0; j < MAT_CLUMN; j ++){
			index = p_mat->mat[i][j].m_picId - 1;
			PicRandNum[index] ++;
		}
	}

	for(i = 0; i < ELEMENT_NUM; i ++){
		Uart_Printf("picRandNum[%d]:%d\r\n", i, PicRandNum[i]);
	}
}

/*****************************************************************
 * 函数名称：changeRandPic
 * 描述说明：改变某种图标的其中一个图标的种类
 * 输入参数：p_mat:连连看逻辑矩阵类指针,picId1:被改变的图标种类值,picId2:要改变成的图标种类值,adjustNum:第几个图标
 * 输出参数：无
*****************************************************************/
void changeRandPic(mat_t *p_mat, int picId1, int picId2, int  adjustNum)
{
	int i, j;

	for(i = 0; i < MAT_ROW; i ++){
		for(j = 0; j < MAT_CLUMN; j ++){
			if(p_mat->mat[i][j].m_picId == picId1){
				adjustNum --;
				if(adjustNum == 0){
					p_mat->mat[i][j].m_picId = picId2;
					return ;
				}
			}
		}
	}
	
}

/*****************************************************************
 * 函数名称：adjustRand
 * 描述说明：将各种类的图标都调整为偶数
 * 输入参数：p_mat:连连看逻辑矩阵类指针
 * 输出参数：无
*****************************************************************/
void adjustRand(mat_t *p_mat)
{
	int i;
	int adjustNum;
	int picId1, picId2;

	for(i = 0; i < ELEMENT_NUM; i ++){
		if(PicRandNum[i] % 2 == 1){
			picId1 = i + 1;
			Uart_Printf("picId1:%d\r\n", picId1);

			i ++;
			while(PicRandNum[i] % 2 == 0){
				i ++;
			}

			picId2 = i + 1;
			adjustNum = getRand(1, PicRandNum[i]);

			changeRandPic(p_mat, picId2, picId1, adjustNum);
		}
	}
}

/*
static char getRand(int min, int max)
{
    static unsigned int rnum = 0xabcd7381;

    rnum = ((rnum * 27) << 8) | (((rnum / 13) & 0xa5a7f196) + (rnum >> 13));

    return(rnum % (max - min + 1)) + min;
}


void printfVmat()
{
	
	int i = 0, j = 0;

	for(i = 0; i < MAT_ROW; i ++){
		for(j = 0; j < MAT_CLUMN; j ++){
			Uart_Printf("%d     ", (int)Vmat[i][j]);
		}
		Uart_Printf("\r\n");
	}
}
*/

void printfMat(mat_t *p_mat)
{
	
	int i = 0, j = 0;

	for(i = 0; i < MAT_ROW; i ++){
		for(j = 0; j < MAT_CLUMN; j ++){
			Uart_Printf("%d     ", (int)p_mat->mat[i][j].m_picId);
		}
		Uart_Printf("\r\n");
	}
}


/*****************************************************************
 * 函数名称：initMat
 * 描述说明：初始化矩阵
 * 输入参数：p_mat:连连看逻辑矩阵类指针,matY:连连图标矩阵显示的开始位置,blockNum:闯关号
 * 输出参数：无
*****************************************************************/
void initMat(mat_t *p_mat, uint16 matY, int blockNum)
{
	int i = 0, j = 0;

	p_mat->m_matY = matY;

#if 0
	for(i = 0; i < MAT_ROW; i ++){
		for(j = 0; j < MAT_CLUMN; j ++){
			initElement(&p_mat->mat[i][j], Vmat[i][j]);
		}
	}
#else
	srand(LoopVal);
	for(i = 0; i < MAT_ROW; i ++){
		for(j = 0; j < MAT_CLUMN; j ++){
			p_mat->mat[i][j].m_picId = 0;
		}
	}

	for(i = 1; i < MAT_ROW - 1; i ++){
		for(j = 1; j < MAT_CLUMN - 1; j ++){
			p_mat->mat[i][j].m_picId = getRand(1, ELEMENT_NUM - 6 + blockNum * 3);
		}
	}

	getPicRandNum(p_mat);
	adjustRand(p_mat);
	getPicRandNum(p_mat);
	
#endif
}



/*****************************************************************
 * 函数名称：showMat
 * 描述说明：显示所有有效的连连看图标
 * 输入参数：p_mat:连连看逻辑矩阵类指针
 * 输出参数：无
*****************************************************************/
void showMat(mat_t *p_mat)
{
	int i = 0, j = 0;

	for(i = 0; i < MAT_ROW; i ++){
		for(j = 0; j < MAT_CLUMN; j ++){
			showElement(&p_mat->mat[i][j], i, j, p_mat->m_matY);
		}
	}
}

/*****************************************************************
 * 函数名称：getLocation
 * 描述说明：获取点击的图标位置
 * 输入参数：p_mat:连连看逻辑矩阵类指针,p_touchXY:点击的坐标指针,p_curLoc:存放点击的位置指针
 * 输出参数：0:没有点击到图标1:有点击到图标
*****************************************************************/
int getLocation(mat_t *p_mat, struct LcdDot *p_touchXY, location_t *p_curLoc)
{
	uint16 x, y;

	x = p_touchXY->x;
	y = p_touchXY->y;
	
	if(y < p_mat->m_matY + ELEMENT_WIDTH || y > p_mat->m_matY + ELEMENT_WIDTH * (MAT_ROW  - 1)||
		x < ELEMENT_WIDTH || x > ELEMENT_WIDTH * (MAT_CLUMN - 1)){
		return 0;
	}

	p_curLoc->clumn = x / ELEMENT_WIDTH;
	p_curLoc->row = (y - p_mat->m_matY) / ELEMENT_WIDTH;

	Uart_Printf("getLocation row:%d, clumn:%d\r\n", p_curLoc->row, p_curLoc->clumn);

	return 1;
}

/*****************************************************************
 * 函数名称：showBoard
 * 描述说明：显示图标边框
 * 输入参数：p_mat:连连看逻辑矩阵类指针,pLocation:显示边框的图标的位置,color:边框颜色值
 * 输出参数：无
*****************************************************************/
void showBoard(mat_t *p_mat, location_t *pLocation, uint16 color )
{
	uint16 x1, y1;
	uint16 x2, y2;

	x1 = pLocation->clumn * ELEMENT_WIDTH;
	y1 = pLocation->row * ELEMENT_WIDTH + p_mat->m_matY;

	x2 = x1 + ELEMENT_WIDTH -1;
	y2 = y1 + ELEMENT_WIDTH -1;
	
	GUI_DrawRect(x1, y1, x2, y2, color);
	GUI_DrawRect(x1 + 1, y1 + 1, x2 - 1 , y2 - 1, color);
}

/*****************************************************************
 * 函数名称：clearPic
 * 描述说明：清除图标
 * 输入参数：p_mat:连连看逻辑矩阵类指针,p_loc:清除边框的图标的位置
 * 输出参数：无
*****************************************************************/
void clearPic(mat_t *p_mat, location_t *p_loc)
{	
	p_mat->mat[p_loc->row][p_loc->clumn].m_picId = 0;
}

/*****************************************************************
 * 函数名称：clearPic
 * 描述说明：用某种颜色覆盖图标的显示
 * 输入参数：p_mat:连连看逻辑矩阵类指针,pLocation:图标的位置,color:要覆盖的颜色
 * 输出参数：无
*****************************************************************/
void clearPicShow(mat_t *p_mat, location_t *pLocation, uint16 color )
{
	uint16 x, y;
	uint16 x1, y1;
	uint16 x2, y2;

	x1 = pLocation->clumn * ELEMENT_WIDTH;
	y1 = pLocation->row * ELEMENT_WIDTH + p_mat->m_matY;

	x2 = x1 + ELEMENT_WIDTH;
	y2 = y1 + ELEMENT_WIDTH;
		
	for( y = y1 ; y < y2 ; y++ ){
		for( x = x1 ; x < x2 ; x++ ){
			LCD_BUFFER[y][x] = color ;
		}
	}
}
