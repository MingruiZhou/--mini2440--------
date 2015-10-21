#include <s3c2440.h>
#include "mmu.h"
#include "IRQ.h"
#include "sys.h"
#include "LCD.h"
#include "adc.h"
#include "gui.h"

#include "ui.h"
#include "myUi.h"
#include "gameUi.h"
#include "share.h"

/*******************************************************
 * 函数名称：main
 * 描述说明：主函数
 * 输入参数：无
 * 输出参数：无
*******************************************************/ 
int main()
{
	int i = 0;
	int ret = 0;

	ui_t startUi, nextUi, timeOutUi, noConnectUi, endUi, winUi;
	gameUi_t gameUi;
	
	// 系统时钟设置初始化
	Set_FCLK(400);				// 设置主频时钟FCLK=400MHz
	Set_ClkDivn(14,12);			// 设置FCLK:HCLK:PCLK=8:2:1

	IRQ_Init();
    Uart0_Init(115200);			// 串口初始化 波特率为115200
 	Lcd_Init();					// LCD初始化
	ADC_Init();					// 触摸屏初始化，等待触摸屏被按下
	Timer0Init();

	initStartUi(&startUi);
	initNextUi(&nextUi);
	initGameUi(&gameUi.m_ui);
	initEndUi(&endUi);
	initTimeOutUi(&timeOutUi);
	initNoConnectUi(&noConnectUi);
	initWinUi(&winUi);


START:
	while(1)
	{
		ret = execWin(&startUi);
		if(ret == BLOCK_NUM + 1){//退出
			if(execWin(&endUi) == 1){
				break;
			}else{
				continue;
			}
		}else{//第i关
			i = ret - 1;
		}
		
		for(; i < BLOCK_NUM; i ++){
			ret = execGame(&gameUi, i);
			switch(ret){
				case 1:{//重新开始当前关
				Uart_Printf("doAgain\r\n");
					i --;
				}
				break;
				
				case 2:{//返回开始界面
				Uart_Printf("doback\r\n");
					goto START;
				}
				break;

				case 3:{//成功闯关
					Uart_Printf("doNext\r\n");
					if(i == BLOCK_NUM - 1){//成功完成游戏
						if(execWin(&winUi) == 1){
							goto START;
						}
					}else if(execWin(&nextUi) == 1){//返回开始页面
						goto START;
					}//否则下一关
				}
				break;

				case 4:{//超时
					Uart_Printf("dotimeOut\r\n");
					if(execWin(&timeOutUi) == 1){
						goto START;
					}else{
						i --;
					}
				}
				break;

				case 5:{//死局
					Uart_Printf("doNoConnect\r\n");
					if(execWin(&noConnectUi) == 1){
						goto START;
					}else{
						i --;
					}
				}
				break;

				default:{

				}
				break;
			};
		}
	}
	Lcd_ClearScr(0);

	return 0;
}
