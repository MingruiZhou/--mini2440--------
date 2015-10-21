#include "gameMng.h"

/*****************************************************************
 * 函数名称：initGameMng
 * 描述说明：初始化gameMng
 * 输入参数：p_gameMng:gameMng指针
 * 输出参数：无
*****************************************************************/
void initGameMng(gameMng_t *p_gameMng)
{
	p_gameMng->curLoc.row = 0;
	p_gameMng->firLoc.row = 0;
	p_gameMng->secLoc.row = 0;
	p_gameMng->m_issec = 0;
	p_gameMng->m_seccNum = 0;
	p_gameMng->m_locSize = 0;
}

/*****************************************************************
 * 函数名称：connectByZero
 * 描述说明：是否是通过两个转弯的连接
 * 输入参数：firLoc:第一次点击的位置,secLoc:第二次点击的位置,p_mat:连连看逻辑矩阵类指针,qIndex:保存连线信息参数
 * 输出参数：0:否1:是
*****************************************************************/
int connectByZero(location_t *firLoc, location_t *secLoc, location_t *locQueue, mat_t *p_mat,uint8 qIndex)
{
	location_t temp = *firLoc;
	int i = 0;
	int dir = 0;
	
	if(temp.row == secLoc->row){
		dir = temp.clumn < secLoc->clumn? 1:-1;
		for(i = temp.clumn + dir; i != secLoc->clumn; i += dir){
			if(p_mat->mat[temp.row][i].m_picId != 0){
				return 0;
			}
		}
	}else if(temp.clumn == secLoc->clumn){
		dir = temp.row < secLoc->row? 1:-1;
		for(i = temp.row + dir; i != secLoc->row; i += dir){
			if(p_mat->mat[i][temp.clumn].m_picId != 0){
				return 0;
			}
		}
	}else{
		return 0;
	}

	locQueue[qIndex] = *firLoc;
	locQueue[qIndex + 1] = *secLoc;
	
	return 1;
}

/*****************************************************************
 * 函数名称：connectByOne
 * 描述说明：是否是通过一个转弯的连接
 * 输入参数：p_gameMng:gameMng指针,p_mat:连连看逻辑矩阵类指针,qIndex:保存连线信息参数
 * 输出参数：0:否1:是
*****************************************************************/
int connectByOne(gameMng_t *p_gameMng, mat_t *p_mat, uint8 qIndex)
{
	location_t firLoc = p_gameMng->firLoc;
	location_t secLoc = p_gameMng->secLoc;
	location_t row_clumn;
	location_t clumn_row;

	row_clumn.row = firLoc.row;
	row_clumn.clumn = secLoc.clumn;

	clumn_row.row = secLoc.row;
	clumn_row.clumn = firLoc.clumn;

	if(p_mat->mat[row_clumn.row][row_clumn.clumn].m_picId == 0 && 
		connectByZero(&p_gameMng->firLoc, &row_clumn, p_gameMng->locQueue, p_mat, qIndex) &&
		connectByZero(&row_clumn, &p_gameMng->secLoc, p_gameMng->locQueue, p_mat, qIndex + 1)){
		return 1;
	}

	if(p_mat->mat[clumn_row.row][clumn_row.clumn].m_picId == 0 &&
		connectByZero(&p_gameMng->firLoc, &clumn_row, p_gameMng->locQueue, p_mat, qIndex) &&
		connectByZero(&clumn_row, &p_gameMng->secLoc, p_gameMng->locQueue, p_mat, qIndex + 1)){
		return 1;
	}

	return 0;
}

/*****************************************************************
 * 函数名称：upConnect
 * 描述说明：向上移动，是否连接
 * 输入参数：p_gameMng:gameMng指针,p_mat:连连看逻辑矩阵类指针
 * 输出参数：0:否1:是
*****************************************************************/
int upConnect(gameMng_t *p_gameMng, mat_t *p_mat)
{
	location_t upLoc = p_gameMng->firLoc;
	location_t temp;

	p_gameMng->locQueue[0] = upLoc;

	for(--upLoc.row; p_mat->mat[upLoc.row][upLoc.clumn].m_picId == 0 && upLoc.row >= 0; upLoc.row --){
		temp.row = upLoc.row;
		temp.clumn = p_gameMng->secLoc.clumn;
		if(p_mat->mat[temp.row][temp.clumn].m_picId == 0&&
			connectByZero(&upLoc, &temp, p_gameMng->locQueue, p_mat, 1) &&
			connectByZero(&temp, &p_gameMng->secLoc, p_gameMng->locQueue, p_mat, 2)){
			return 1;
		}
	}

	return 0;
}

/*****************************************************************
 * 函数名称：downConnect
 * 描述说明：向下移动，是否连接
 * 输入参数：p_gameMng:gameMng指针,p_mat:连连看逻辑矩阵类指针
 * 输出参数：0:否1:是
*****************************************************************/
int downConnect(gameMng_t *p_gameMng, mat_t *p_mat)
{
	location_t downLoc = p_gameMng->firLoc;
	location_t temp;

	p_gameMng->locQueue[0] = downLoc;

	for(++downLoc.row; p_mat->mat[downLoc.row][downLoc.clumn].m_picId == 0 && downLoc.row <= MAT_ROW; downLoc.row ++){
		temp.row = downLoc.row;
		temp.clumn = p_gameMng->secLoc.clumn;
		if(p_mat->mat[temp.row][temp.clumn].m_picId == 0 &&
			connectByZero(&downLoc, &temp, p_gameMng->locQueue, p_mat, 1) &&
			connectByZero(&temp, &p_gameMng->secLoc, p_gameMng->locQueue, p_mat, 2)){
			return 1;
		}
	}

	return 0;
}

/*****************************************************************
 * 函数名称：leftConnect
 * 描述说明：向左移动，是否连接
 * 输入参数：p_gameMng:gameMng指针,p_mat:连连看逻辑矩阵类指针
 * 输出参数：0:否1:是
*****************************************************************/
int leftConnect(gameMng_t *p_gameMng, mat_t *p_mat)
{
	location_t leftLoc = p_gameMng->firLoc;
	location_t temp;

	p_gameMng->locQueue[0] = leftLoc;

	for(--leftLoc.clumn; p_mat->mat[leftLoc.row][leftLoc.clumn].m_picId == 0 && leftLoc.clumn >= 0; leftLoc.clumn --){
		temp.row = p_gameMng->secLoc.row;
		temp.clumn = leftLoc.clumn;
		if(p_mat->mat[temp.row][temp.clumn].m_picId == 0 &&
			connectByZero(&leftLoc, &temp, p_gameMng->locQueue, p_mat, 1) &&
			connectByZero(&temp, &p_gameMng->secLoc, p_gameMng->locQueue, p_mat, 2)){
			return 1;
		}
	}
	
	return 0;
}

/*****************************************************************
 * 函数名称：rightConnect
 * 描述说明：向右移动，是否连接
 * 输入参数：p_gameMng:gameMng指针,p_mat:连连看逻辑矩阵类指针
 * 输出参数：0:否1:是
*****************************************************************/
int rightConnect(gameMng_t *p_gameMng, mat_t *p_mat)
{
	location_t rightLoc = p_gameMng->firLoc;
	location_t temp;

	p_gameMng->locQueue[0] = rightLoc;

	for(++rightLoc.clumn; p_mat->mat[rightLoc.row][rightLoc.clumn].m_picId == 0 && rightLoc.clumn <= MAT_CLUMN; rightLoc.clumn ++){
		temp.row = p_gameMng->secLoc.row;
		temp.clumn = rightLoc.clumn;
		if(p_mat->mat[temp.row][temp.clumn].m_picId == 0 &&
			connectByZero(&rightLoc, &temp, p_gameMng->locQueue, p_mat, 1) &&
			connectByZero(&temp, &p_gameMng->secLoc, p_gameMng->locQueue, p_mat, 2)){
			return 1;
		}
	}

	return 0;
}

/*****************************************************************
 * 函数名称：connectByTwo
 * 描述说明：是否是通过两个转弯的连接
 * 输入参数：p_gameMng:gameMng指针,p_mat:连连看逻辑矩阵类指针
 * 输出参数：0:否1:是
*****************************************************************/
int connectByTwo(gameMng_t *p_gameMng, mat_t *p_mat)
{
	if(upConnect(p_gameMng, p_mat) == 1 ||
		downConnect(p_gameMng, p_mat) == 1 ||
		leftConnect(p_gameMng, p_mat) == 1 ||
		rightConnect(p_gameMng, p_mat) == 1){

		return 1;
	}

	return 0;
}

void  drawLInkLine(gameMng_t *p_gameMng, mat_t *p_mat, uint16 color, int linkSize)
{
	int i, j;
	location_t loc1, loc2;
	uint16 left, top, right, bottom;
	
	for(i = 0; i + 1 < p_gameMng->m_locSize; i ++){
		loc1 = p_gameMng->locQueue[i];
		loc2 = p_gameMng->locQueue[i + 1];

		left = loc1.clumn * ELEMENT_WIDTH + ELEMENT_WIDTH / 2;
		right = loc2.clumn * ELEMENT_WIDTH + ELEMENT_WIDTH / 2;
		top = loc1.row * ELEMENT_WIDTH + ELEMENT_WIDTH / 2 + p_mat->m_matY;
		bottom = loc2.row * ELEMENT_WIDTH + ELEMENT_WIDTH / 2 + p_mat->m_matY;
		
		if(loc1.row == loc2.row){
			for(j = 0; j < linkSize; j ++){
				GUI_DrawHLine(left, top + j, right, color);
			}
		}else if(loc1.clumn== loc2.clumn){
			for(j = 0; j < linkSize; j ++){
				GUI_DrawVLine(left + j, top, bottom, color);
			}
		}
	}
}

/*****************************************************************
 * 函数名称：isConnect
 * 描述说明：两次点击是否成功,并保存相关的连线信息
 * 输入参数：p_gameMng:gameMng指针,p_mat:连连看逻辑矩阵类指针
 * 输出参数：0:否1:是
*****************************************************************/
int isConnect(gameMng_t *p_gameMng, mat_t *p_mat)
{
	if(p_gameMng->firLoc.row  ==  p_gameMng->secLoc.row &&
	 	p_gameMng->firLoc.clumn  ==  p_gameMng->secLoc.clumn){
		return 0;
	}

	if(p_mat->mat[p_gameMng->firLoc.row][p_gameMng->firLoc.clumn].m_picId != p_mat->mat[p_gameMng->secLoc.row][p_gameMng->secLoc.clumn].m_picId){
		return 0;
	}

	if(connectByZero(&p_gameMng->firLoc, &p_gameMng->secLoc, p_gameMng->locQueue, p_mat,0)){
		p_gameMng->m_locSize = 2;
		return 1;
	}else if(connectByOne(p_gameMng, p_mat, 0)){
		p_gameMng->m_locSize = 3;
		return 1;
	}else if(connectByTwo(p_gameMng, p_mat)){
		p_gameMng->m_locSize = 4;
		return 1;
	}else{
		p_gameMng->m_locSize = 0;
		return 0;
	}
}

/*****************************************************************
 * 函数名称：seccess
 * 描述说明：是否消除了所有图标
 * 输入参数：p_gameMng:gameMng指针
 * 输出参数：0:否1:是
*****************************************************************/
int seccess(gameMng_t *p_gamMng)
{
	if(p_gamMng->m_seccNum >= (MAT_CLUMN -2) * (MAT_ROW - 2) / 2){
		return 1;
	}

	return 0;
}

/*****************************************************************
 * 函数名称：doGame
 * 描述说明：进行游戏管理
 * 输入参数：p_gameMng:gameMng指针,p_mat:连连看逻辑矩阵类指针,p_touchXY:点击坐标指针
 * 输出参数：0:点击坐标不在矩阵内1:第一次点击2:第二次点击
*****************************************************************/
int doGame(gameMng_t *p_gameMng, mat_t *p_mat, struct LcdDot *p_touchXY)
{
	int ret = 0;
	
	ret = getLocation(p_mat, p_touchXY, &p_gameMng->curLoc);

	if(ret){
		if(p_mat->mat[p_gameMng->curLoc.row][p_gameMng->curLoc.clumn].m_picId != 0){
			if(p_gameMng->m_issec == 0){
				p_gameMng->firLoc = p_gameMng->curLoc;
				showBoard(p_mat, &p_gameMng->firLoc, BOARD_COLOR);
				p_gameMng->m_issec = 1;

				return 1;//点击第一个
			}else{
				p_gameMng->secLoc= p_gameMng->curLoc;
				showBoard(p_mat, &p_gameMng->secLoc, BOARD_COLOR);
				p_gameMng->m_issec = 0;

				if(isConnect(p_gameMng, p_mat)){
					drawLInkLine(p_gameMng, p_mat, LINK_LINE_COLOR, LINK_LINE_SIZE);
					gameDelay(1000);
					drawLInkLine(p_gameMng, p_mat, 0xffff, LINK_LINE_SIZE);
					clearPicShow(p_mat, &p_gameMng->firLoc, 0xffff);
					clearPicShow(p_mat, &p_gameMng->secLoc, 0xffff);
					
					clearPic(p_mat, &p_gameMng->firLoc);
					clearPic(p_mat, &p_gameMng->secLoc);
					p_gameMng->m_locSize = 0;
					p_gameMng->m_seccNum++;
					noConnectTime = 0;
				}else{
					gameDelay(1000);
					showBoard(p_mat, &p_gameMng->firLoc, 0xffff);
					showBoard(p_mat, &p_gameMng->secLoc, 0xffff);
				}

				return 2;//点击第二个
			}
		}else{
			if(p_gameMng->m_issec == 0){
				return 1;
			}else{
				p_gameMng->m_issec = 0;
				showBoard(p_mat, &p_gameMng->firLoc, 0xffff);
				showBoard(p_mat, &p_gameMng->secLoc, 0xffff);
				return 2;
			}
		}
	}else{
		showBoard(p_mat, &p_gameMng->firLoc, 0xffff);
		showBoard(p_mat, &p_gameMng->secLoc, 0xffff);
		p_gameMng->m_issec = 0;
		return 0;
	}

	return 0;
}
