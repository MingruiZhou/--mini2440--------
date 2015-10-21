#include "gameUi.h"
#include "myUi.h"

/*****************************************************************
 * �������ƣ�initGame
 * ����˵������ʼ����������Ϸ
 * ���������p_gameUi:��Ϸ��ָ��,blockNum:��ǰ����
 * �����������
*****************************************************************/
void initGame(gameUi_t *p_gameUi, int blockNum)
{
	p_gameUi->m_matY = 40;
	initMat(&p_gameUi->m_mat, p_gameUi->m_matY, blockNum);
	initGameMng(&p_gameUi->m_gameMng);
}

/*****************************************************************
 * �������ƣ�showGame
 * ����˵������ʾ��������Ϸ
 * ���������p_gameUi:��Ϸ��ָ��
 * �����������
*****************************************************************/
void showGame(gameUi_t *p_gameUi)
{
	showWin(&p_gameUi->m_ui);
	showMat(&p_gameUi->m_mat);
	showTime(restTime);
}

/*****************************************************************
 * �������ƣ�haveConnect
 * ����˵�����ж��Ƿ�����
 * ���������p_mat:�������߼�������ָ��
 * ���������0:����1:δ����
*****************************************************************/
int haveConnect(mat_t *p_mat)
{
	int i, j;
	int max;
	gameMng_t gameMng;

	max = MAT_ROW * MAT_CLUMN;

	for(i = 0; i < max; i ++){
		if(p_mat->mat[i / MAT_ROW][i % MAT_ROW].m_picId != 0){
			gameMng.firLoc.row = i / MAT_ROW;
			gameMng.firLoc.clumn = i % MAT_ROW;
			for(j = i + 1; j < max; j ++){
				if(p_mat->mat[j / MAT_ROW][j % MAT_ROW].m_picId != 0){
					gameMng.secLoc.row = j / MAT_ROW;
					gameMng.secLoc.clumn = j % MAT_ROW;
					if(isConnect(&gameMng, p_mat)){
						return 1;
					}
				}
			}
		}
	}

	return 0;
}

/*****************************************************************
 * �������ƣ�execGame
 * ����˵����������������Ϸ
 * ���������p_gameUi:��Ϸ��ָ��,blockNum:��ǰ����
 * ���������1:���¿�ʼ��ǰ��2:����3:���سɹ�4:��ʱ5:����
*****************************************************************/
int execGame(gameUi_t *p_gameUi, int blockNum)
{
	int ret = 0;
	struct LcdDot touchXY;

	gameExeFlag = 1;
	restTime = 75;
	noConnectTime = 0;
	initGame(p_gameUi, blockNum);
	showGame(p_gameUi);
	
	while(1){
		while(GetTouch(&touchXY) == 0);

		if(restTime <= 0){
			gameExeFlag = 0;
			return 4;
		}

		if(noConnectTime > 3){
			if(haveConnect(&p_gameUi->m_mat) == 0){
				gameExeFlag = 0;
				return 5;
			}else{
				noConnectTime = 0;
			}
		}

		ret = doGame(&p_gameUi->m_gameMng, &p_gameUi->m_mat, &touchXY);
		if(ret != 0){//���ھ�����
			if(ret == 2){//����ڶ���
				if(seccess(&p_gameUi->m_gameMng)){
					gameExeFlag = 0;
					return 3;
				}else{
					//gameDelay(1000);
					//showGame(p_gameUi);	
				}
			}
		}else{//���ھ�����
			//showGame(p_gameUi);
			ret = getMenu(&p_gameUi->m_ui, &touchXY);

			if(ret > 0){
				gameExeFlag = 0;
				return ret;
			}
		}
	}

	return 0;
}


