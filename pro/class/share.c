#include "share.h"
#include "LCD.h"

unsigned long LoopVal;
int restTime;
int noConnectTime;
int gameExeFlag;

void gameDelay(int count)
{
	int i;
	
	while(count --){
		for(i = 0; i < 10000; i ++){

		}
	}
}

/*****************************************************************
 * 函数名称：showTime
 * 描述说明：显示倒计时剩余的时间
 * 输入参数：restTime:剩下的时间值
 * 输出参数：无
*****************************************************************/
void showTime(int restTime)
{
	Lcd_printf(20, 30, 0, 0xffff, 1, "剩余时间%2d秒", restTime);
}

/*****************************************************************
 * 函数名称：myTime0Handle
 * 描述说明：定时器中断程序
 * 输入参数：无
 * 输出参数：无
*****************************************************************/
void myTime0Handle()
{
	if(gameExeFlag == 1){
		showTime(restTime);
		if(restTime > 0){
			noConnectTime ++;
			restTime --;
		}
	}
	Uart_Printf("loopVal:%d, noConnectTime:%d\r\n", LoopVal, noConnectTime);
	Uart_Printf("restTime:%d, gameExeFlag:%d\r\n", restTime, gameExeFlag);
}


