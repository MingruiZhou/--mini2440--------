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
 * �������ƣ�main
 * ����˵����������
 * �����������
 * �����������
*******************************************************/ 
int main()
{
	int i = 0;
	int ret = 0;

	ui_t startUi, nextUi, timeOutUi, noConnectUi, endUi, winUi;
	gameUi_t gameUi;
	
	// ϵͳʱ�����ó�ʼ��
	Set_FCLK(400);				// ������Ƶʱ��FCLK=400MHz
	Set_ClkDivn(14,12);			// ����FCLK:HCLK:PCLK=8:2:1

	IRQ_Init();
    Uart0_Init(115200);			// ���ڳ�ʼ�� ������Ϊ115200
 	Lcd_Init();					// LCD��ʼ��
	ADC_Init();					// ��������ʼ�����ȴ�������������
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
		if(ret == BLOCK_NUM + 1){//�˳�
			if(execWin(&endUi) == 1){
				break;
			}else{
				continue;
			}
		}else{//��i��
			i = ret - 1;
		}
		
		for(; i < BLOCK_NUM; i ++){
			ret = execGame(&gameUi, i);
			switch(ret){
				case 1:{//���¿�ʼ��ǰ��
				Uart_Printf("doAgain\r\n");
					i --;
				}
				break;
				
				case 2:{//���ؿ�ʼ����
				Uart_Printf("doback\r\n");
					goto START;
				}
				break;

				case 3:{//�ɹ�����
					Uart_Printf("doNext\r\n");
					if(i == BLOCK_NUM - 1){//�ɹ������Ϸ
						if(execWin(&winUi) == 1){
							goto START;
						}
					}else if(execWin(&nextUi) == 1){//���ؿ�ʼҳ��
						goto START;
					}//������һ��
				}
				break;

				case 4:{//��ʱ
					Uart_Printf("dotimeOut\r\n");
					if(execWin(&timeOutUi) == 1){
						goto START;
					}else{
						i --;
					}
				}
				break;

				case 5:{//����
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
