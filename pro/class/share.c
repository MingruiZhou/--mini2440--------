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
 * �������ƣ�showTime
 * ����˵������ʾ����ʱʣ���ʱ��
 * ���������restTime:ʣ�µ�ʱ��ֵ
 * �����������
*****************************************************************/
void showTime(int restTime)
{
	Lcd_printf(20, 30, 0, 0xffff, 1, "ʣ��ʱ��%2d��", restTime);
}

/*****************************************************************
 * �������ƣ�myTime0Handle
 * ����˵������ʱ���жϳ���
 * �����������
 * �����������
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


