#include "gameUi.h"
#include "myUi.h"

/*****************************************************************
 * 函数名称：initGame
 * 描述说明：初始化连连看游戏
 * 输入参数：p_gameUi:游戏体指针,blockNum:当前关数
 * 输出参数：无
*****************************************************************/
void initGame(gameUi_t *p_gameUi, int blockNum)
{
	p_gameUi->m_matY = 40;
	initMat(&p_gameUi->m_mat, p_gameUi->m_matY, blockNum);
	initGameMng(&p_gameUi->m_gameMng);
}

/*****************************************************************
 * 函数名称：showGame
 * 描述说明：显示连连看游戏
 * 输入参数：p_gameUi:游戏体指针
 * 输出参数：无
*****************************************************************/
void showGame(gameUi_t *p_gameUi)
{
	showWin(&p_gameUi->m_ui);
	showMat(&p_gameUi->m_mat);
	showTime(restTime);
}

/*****************************************************************
 * 函数名称：haveConnect
 * 描述说明：判断是否死局
 * 输入参数：p_mat:连连看逻辑矩阵类指针
 * 输出参数：0:死局1:未死局
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
 * 函数名称：execGame
 * 描述说明：运行连连看游戏
 * 输入参数：p_gameUi:游戏体指针,blockNum:当前关数
 * 输出参数：1:重新开始当前关2:返回3:闯关成功4:超时5:死局
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
		if(ret != 0){//按在矩阵内
			if(ret == 2){//点击第二次
				if(seccess(&p_gameUi->m_gameMng)){
					gameExeFlag = 0;
					return 3;
				}else{
					//gameDelay(1000);
					//showGame(p_gameUi);	
				}
			}
		}else{//按在矩阵外
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


