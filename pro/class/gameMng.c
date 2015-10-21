#include "gameMng.h"

/*****************************************************************
 * �������ƣ�initGameMng
 * ����˵������ʼ��gameMng
 * ���������p_gameMng:gameMngָ��
 * �����������
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
 * �������ƣ�connectByZero
 * ����˵�����Ƿ���ͨ������ת�������
 * ���������firLoc:��һ�ε����λ��,secLoc:�ڶ��ε����λ��,p_mat:�������߼�������ָ��,qIndex:����������Ϣ����
 * ���������0:��1:��
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
 * �������ƣ�connectByOne
 * ����˵�����Ƿ���ͨ��һ��ת�������
 * ���������p_gameMng:gameMngָ��,p_mat:�������߼�������ָ��,qIndex:����������Ϣ����
 * ���������0:��1:��
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
 * �������ƣ�upConnect
 * ����˵���������ƶ����Ƿ�����
 * ���������p_gameMng:gameMngָ��,p_mat:�������߼�������ָ��
 * ���������0:��1:��
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
 * �������ƣ�downConnect
 * ����˵���������ƶ����Ƿ�����
 * ���������p_gameMng:gameMngָ��,p_mat:�������߼�������ָ��
 * ���������0:��1:��
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
 * �������ƣ�leftConnect
 * ����˵���������ƶ����Ƿ�����
 * ���������p_gameMng:gameMngָ��,p_mat:�������߼�������ָ��
 * ���������0:��1:��
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
 * �������ƣ�rightConnect
 * ����˵���������ƶ����Ƿ�����
 * ���������p_gameMng:gameMngָ��,p_mat:�������߼�������ָ��
 * ���������0:��1:��
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
 * �������ƣ�connectByTwo
 * ����˵�����Ƿ���ͨ������ת�������
 * ���������p_gameMng:gameMngָ��,p_mat:�������߼�������ָ��
 * ���������0:��1:��
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
 * �������ƣ�isConnect
 * ����˵�������ε���Ƿ�ɹ�,��������ص�������Ϣ
 * ���������p_gameMng:gameMngָ��,p_mat:�������߼�������ָ��
 * ���������0:��1:��
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
 * �������ƣ�seccess
 * ����˵�����Ƿ�����������ͼ��
 * ���������p_gameMng:gameMngָ��
 * ���������0:��1:��
*****************************************************************/
int seccess(gameMng_t *p_gamMng)
{
	if(p_gamMng->m_seccNum >= (MAT_CLUMN -2) * (MAT_ROW - 2) / 2){
		return 1;
	}

	return 0;
}

/*****************************************************************
 * �������ƣ�doGame
 * ����˵����������Ϸ����
 * ���������p_gameMng:gameMngָ��,p_mat:�������߼�������ָ��,p_touchXY:�������ָ��
 * ���������0:������겻�ھ�����1:��һ�ε��2:�ڶ��ε��
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

				return 1;//�����һ��
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

				return 2;//����ڶ���
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
