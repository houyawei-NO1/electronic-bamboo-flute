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
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序            */
/*---------------------------------------------------------------------*/

//#include	"\..\library\config.h"
#include	"\..\library\STC32G_GPIO.h"
#include	"\..\library\STC32G_Delay.h"
#include	"\..\library\STC32G_UART.h"
#include	"\..\library\STC32G_NVIC.h"//中断
#include	"\..\library\STC32G_Switch.h"//功能脚切换

/***************	功能说明	****************

程序使用P6口来演示跑马灯。

下载时, 选择时钟 24MHz (可以在配置文件"config.h"中修改).

******************************************/

//========================================================================
//                               本地常量声明	
//========================================================================

u8 code ledNum[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

//========================================================================
//                               本地变量声明
//========================================================================

u8 ledIndex;

//========================================================================
// 函数: GPIO_config
// 描述: 用户初始化程序.
// 参数: None.
// 返回: None.
// 版本: V1.0, 2020-09-28
//========================================================================
void GPIO_config(void)
{
	P3_MODE_IO_PU(GPIO_Pin_5);			//P3.5设置为准双向口
	P3_MODE_IO_PU(GPIO_Pin_4);		//P3.4 设置为准双向口
}

/***************  串口初始化函数 *****************/
void	UART_config(void)
{
	COMx_InitDefine		COMx_InitStructure;					//结构定义
	COMx_InitStructure.UART_Mode      = UART_8bit_BRTx;		//模式,   UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			//选择波特率发生器, BRT_Timer1,BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
	COMx_InitStructure.UART_BaudRate  = 115200ul;			//波特率,     110 ~ 115200
	COMx_InitStructure.UART_RxEnable  = ENABLE;				//接收允许,   ENABLE或DISABLE
	UART_Configuration(UART1, &COMx_InitStructure);		//初始化串口 UART1,UART2,UART3,UART4
	NVIC_UART1_Init(ENABLE,Priority_1);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3

	UART1_SW(UART1_SW_P30_P31);		//UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17,UART1_SW_P43_P44
}

//========================================================================
// 函数: main
// 描述: 用户应用程序.
// 参数: None.
// 返回: None.
// 版本: V1.0, 2020-09-23
//========================================================================
void main(void)
{
	WTST = 0;		//设置程序指令延时参数，赋值为0可将CPU执行指令的速度设置为最快
	EAXSFR();		//扩展SFR(XFR)访问使能 
	CKCON = 0;      //提高访问XRAM速度

	GPIO_config();
	P35 = 0;		
	UART_config();
	EA = 1;

	printf("STC32G AD to UART Test Programme!\r\n");	//UART发送一个字符串
	
	while(1)
	{
		delay_ms(1000);
		P34 = ~P34;	//输出低驱动
		printf("STC32G AD to UART Test Programme!\r\n");	//UART发送一个字符串
//		ledIndex++;
//		if(ledIndex > 7)
//		{
//			ledIndex = 0;
//		}
	}
}




