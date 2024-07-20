#include	"\..\library\config.h"
#include	"\..\library\STC32G_GPIO.h"
#include	"\..\library\STC32G_Delay.h"
#include	"\..\library\STC32G_UART.h"
#include	"\..\library\STC32G_ADC.h"
#include	"\..\library\STC32G_PWM.h"
#include	"\..\library\STC32G_NVIC.h"//�ж�
#include	"\..\library\STC32G_Switch.h"//���ܽ��л�
#include   "gpio_interrupt.h"
//#include   "ebf_control.h"

//����ʱ, ѡ��ʱ�� 12MHz (�����������ļ�"config.h"���޸�).

/*************	���س�������	**************/

u16 code Sound_Fre[4][7]=          //������
{                           
        45627        ,40677        ,36253        ,34285        ,30534        ,27210        ,24242,//����
        22900        ,20408        ,18181        ,17167        ,15286        ,13620        ,12133,//����
        11450        ,10204        ,9022         ,8583         ,7648         ,6814         ,6069,//����
        5730         ,5106         ,4548         ,4293         ,3825         ,3408         ,3036,//������
} ;        


/*************	���ر�������	**************/

PWMx_Duty PWMA_Duty;
bit PWM1_Flag;
u8 i;
u8 j;
//bit one_f,two_f,three_f,four_f,five_f,six_f,low_f,high_f;
/*************	���غ�������	**************/
void	PWM_config(u16 Fre);
void	UART_config(void);
void    GPIO_config(void);
void	controlbeep(void);
/*************  �ⲿ�����ͱ������� *****************/






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
//	GPIO_INT_Config(GPIO_P0, INT_FALL, Pin0 | Pin1 | Pin2 | Pin3);	
//	GPIO_INT_Config(GPIO_P2, INT_FALL, Pin4 | Pin5 | Pin6 | Pin7);
	//��ͨIO�ж����ú���, �ж�ģʽ(ֻȡ��һ): INT_FALL, INT_RISE, INT_LOW, INT_HIGH. �ֱ��� ������ �½��� �͵�ƽ  �ߵ�ƽ �ж�.
	P35 = 0;		
	UART_config();
	PWM_config(45627);
	EA = 1;

	printf("STC32G AD to UART Test Programme!\r\n");	//UART����һ���ַ���
//	one_f=0,two_f=0,three_f=0,four_f=0,five_f=0,six_f=0,low_f=0,high_f=0;
	
	while(1)
	{
		delay_ms(200);
//		P34 = ~P34;	//���������
//		printf("STC32G AD to UART Test Programme!\r\n");	//UART����һ���ַ���
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
	
	P0_MODE_IO_PU(GPIO_Pin_All);			//P0 ����Ϊ׼˫���
	P2_MODE_IO_PU(GPIO_Pin_All);			//P2 ����Ϊ׼˫���
//������PWM���ܺ�������Զ�����Ϊ�������ģʽ��
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

/***************  PWM��ʼ������ *****************/
void	PWM_config(u16 Fre)
{
	PWMx_InitDefine		PWMx_InitStructure;
	
	PWMx_InitStructure.PWM_Period   = Fre;							//����ʱ��,   0~65535
	PWMA_Duty.PWM1_Duty = PWMx_InitStructure.PWM_Period / 2;

	PWMx_InitStructure.PWM_Mode    =	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty    = PWMA_Duty.PWM1_Duty;	//PWMռ�ձ�ʱ��, 0~Period
	PWMx_InitStructure.PWM_EnoSelect   = ENO1P;
	PWM_Configuration(PWM1, &PWMx_InitStructure);				//��ʼ��PWM1

	PWMx_InitStructure.PWM_DeadTime = 0;								//��������������, 0~255
	PWMx_InitStructure.PWM_MainOutEnable= ENABLE;				//�����ʹ��, ENABLE,DISABLE
	PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;				//ʹ�ܼ�����, ENABLE,DISABLE
	PWM_Configuration(PWMA, &PWMx_InitStructure);				//��ʼ��PWMͨ�üĴ���,  PWMA,PWMB
	
	
	PWM1_USE_P10P11();

	NVIC_PWM_Init(PWMA,DISABLE,Priority_0);

}


