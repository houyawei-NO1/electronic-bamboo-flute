/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- BBS: www.STCAIMCU.com  -----------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����            */
/*---------------------------------------------------------------------*/

//#include	"\..\library\config.h"
#include	"\..\library\STC32G_GPIO.h"
#include	"\..\library\STC32G_Delay.h"
#include	"\..\library\STC32G_UART.h"
#include	"\..\library\STC32G_NVIC.h"//�ж�
#include	"\..\library\STC32G_Switch.h"//���ܽ��л�

/***************	����˵��	****************

����ʹ��P6������ʾ����ơ�

����ʱ, ѡ��ʱ�� 24MHz (�����������ļ�"config.h"���޸�).

******************************************/

//========================================================================
//                               ���س�������	
//========================================================================

u8 code ledNum[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

//========================================================================
//                               ���ر�������
//========================================================================

u8 ledIndex;

//========================================================================
// ����: GPIO_config
// ����: �û���ʼ������.
// ����: None.
// ����: None.
// �汾: V1.0, 2020-09-28
//========================================================================
void GPIO_config(void)
{
	P3_MODE_IO_PU(GPIO_Pin_5);			//P3.5����Ϊ׼˫���
	P3_MODE_IO_PU(GPIO_Pin_4);		//P3.4 ����Ϊ׼˫���
}

/***************  ���ڳ�ʼ������ *****************/
void	UART_config(void)
{
	COMx_InitDefine		COMx_InitStructure;					//�ṹ����
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//ģʽ,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//ѡ�����ʷ�����, BRT_Timer1,BRT_Timer2 (ע��: ����2�̶�ʹ��BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//������,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//��������,   ENABLE��DISABLE
	UART_Configuration(UART1, &COMx_InitStructure);		//��ʼ������ UART1,UART2,UART3,UART4
	NVIC_UART1_Init(ENABLE,Priority_1);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3

	UART1_SW(UART1_SW_P30_P31);		//UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
}

//========================================================================
// ����: main
// ����: �û�Ӧ�ó���.
// ����: None.
// ����: None.
// �汾: V1.0, 2020-09-23
//========================================================================
void main(void)
{
	WTST = 0;		//���ó���ָ����ʱ��������ֵΪ0�ɽ�CPUִ��ָ����ٶ�����Ϊ���
	EAXSFR();		//��չSFR(XFR)����ʹ�� 
	CKCON = 0;      //��߷���XRAM�ٶ�

	GPIO_config();
	P35 = 0;		
	UART_config();
	EA = 1;

	printf("STC32G AD to UART Test Programme!\r\n");	//UART����һ���ַ���
	
	while(1)
	{
		delay_ms(1000);
		P34 = ~P34;	//���������
		printf("STC32G AD to UART Test Programme!\r\n");	//UART����һ���ַ���
//		ledIndex++;
//		if(ledIndex > 7)
//		{
//			ledIndex = 0;
//		}
	}
}




