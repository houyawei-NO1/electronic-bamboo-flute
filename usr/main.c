#include	"\..\library\config.h"
#include	"\..\library\STC32G_GPIO.h"
#include	"\..\library\STC32G_Delay.h"
#include	"\..\library\STC32G_UART.h"
#include	"\..\library\STC32G_ADC.h"
#include	"\..\library\STC32G_PWM.h"
#include	"\..\library\STC32G_NVIC.h"//中断
#include	"\..\library\STC32G_Switch.h"//功能脚切换
#include   "gpio_interrupt.h"
//#include   "ebf_control.h"

//下载时, 选择时钟 12MHz (可以在配置文件"config.h"中修改).

/*************	本地常量声明	**************/

u16 code Sound_Fre[4][7]=          //声音库
{                           
        45627        ,40677        ,36253        ,34285        ,30534        ,27210        ,24242,//低音
        22900        ,20408        ,18181        ,17167        ,15286        ,13620        ,12133,//中音
        11450        ,10204        ,9022         ,8583         ,7648         ,6814         ,6069,//高音
        5730         ,5106         ,4548         ,4293         ,3825         ,3408         ,3036,//超高音
} ;        


/*************	本地变量声明	**************/

PWMx_Duty PWMA_Duty;
bit PWM1_Flag;
u8 i;
u8 j;
//bit one_f,two_f,three_f,four_f,five_f,six_f,low_f,high_f;
/*************	本地函数声明	**************/
void	PWM_config(u16 Fre);
void	UART_config(void);
void    GPIO_config(void);
void	controlbeep(void);
/*************  外部函数和变量声明 *****************/






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
//	GPIO_INT_Config(GPIO_P0, INT_FALL, Pin0 | Pin1 | Pin2 | Pin3);	
//	GPIO_INT_Config(GPIO_P2, INT_FALL, Pin4 | Pin5 | Pin6 | Pin7);
	//普通IO中断配置函数, 中断模式(只取其一): INT_FALL, INT_RISE, INT_LOW, INT_HIGH. 分别是 上升沿 下降沿 低电平  高电平 中断.
	P35 = 0;		
	UART_config();
	PWM_config(45627);
	EA = 1;

	printf("STC32G AD to UART Test Programme!\r\n");	//UART发送一个字符串
//	one_f=0,two_f=0,three_f=0,four_f=0,five_f=0,six_f=0,low_f=0,high_f=0;
	
	while(1)
	{
		delay_ms(200);
//		P34 = ~P34;	//输出低驱动
//		printf("STC32G AD to UART Test Programme!\r\n");	//UART发送一个字符串
//		PWMA_Duty.PWM1_Duty = 128;
//		UpdatePwm(PWMA, &PWMA_Duty);
		
		
//		for(i=0;i<=3;i++)
//			{
//			for(j=0;j<=6;j++)
//				{
//				PWM_config(Sound_Fre[i][j]);
//				printf("i:%hd,j:%hd,Fre:%ld\r\n",i,j,Sound_Fre[i][j]);
//				delay_ms(5000);
//				}
//			}
		controlbeep();
//		one_f=0,two_f=0,three_f=0,four_f=0,five_f=0,six_f=0,low_f=0,high_f=0;

	}
}

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
	
	P0_MODE_IO_PU(GPIO_Pin_All);			//P0 设置为准双向口
	P2_MODE_IO_PU(GPIO_Pin_All);			//P2 设置为准双向口
//（启动PWM功能后输出脚自动设置为推挽输出模式）
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

/***************  PWM初始化函数 *****************/
void	PWM_config(u16 Fre)
{
	PWMx_InitDefine		PWMx_InitStructure;
	
	PWMx_InitStructure.PWM_Period   = Fre;							//周期时间,   0~65535
	PWMA_Duty.PWM1_Duty = PWMx_InitStructure.PWM_Period / 2;

	PWMx_InitStructure.PWM_Mode    =	CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty    = PWMA_Duty.PWM1_Duty;	//PWM占空比时间, 0~Period
	PWMx_InitStructure.PWM_EnoSelect   = ENO1P;
	PWM_Configuration(PWM1, &PWMx_InitStructure);				//初始化PWM1

	PWMx_InitStructure.PWM_DeadTime = 0;								//死区发生器设置, 0~255
	PWMx_InitStructure.PWM_MainOutEnable= ENABLE;				//主输出使能, ENABLE,DISABLE
	PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;				//使能计数器, ENABLE,DISABLE
	PWM_Configuration(PWMA, &PWMx_InitStructure);				//初始化PWM通用寄存器,  PWMA,PWMB
	
	
	PWM1_USE_P10P11();

	NVIC_PWM_Init(PWMA,DISABLE,Priority_0);

}


