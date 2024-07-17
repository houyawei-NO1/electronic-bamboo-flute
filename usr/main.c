//#include	"\..\library\config.h"
#include	"\..\library\STC32G_GPIO.h"
#include	"\..\library\STC32G_Delay.h"
#include	"\..\library\STC32G_UART.h"
#include	"\..\library\STC32G_ADC.h"
#include	"\..\library\STC32G_PWM.h"
#include	"\..\library\STC32G_NVIC.h"//�ж�
#include	"\..\library\STC32G_Switch.h"//���ܽ��л�

//����ʱ, ѡ��ʱ�� 24MHz (�����������ļ�"config.h"���޸�).

/*************	���س�������	**************/


/*************	���ر�������	**************/

PWMx_Duty PWMA_Duty;
bit PWM1_Flag;
bit PWM2_Flag;
bit PWM3_Flag;
bit PWM4_Flag;

/*************	���غ�������	**************/
void	PWM_config(void);
void	UART_config(void);
void    GPIO_config(void);
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
	P35 = 0;		
	UART_config();
	PWM_config();
	EA = 1;

	printf("STC32G AD to UART Test Programme!\r\n");	//UART����һ���ַ���
	
	while(1)
	{
		delay_ms(1000);
		P34 = ~P34;	//���������
		printf("STC32G AD to UART Test Programme!\r\n");	//UART����һ���ַ���

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
void	PWM_config(void)
{
	PWMx_InitDefine		PWMx_InitStructure;
	
	PWMA_Duty.PWM1_Duty = 128;
	PWMA_Duty.PWM2_Duty = 256;
	PWMA_Duty.PWM3_Duty = 512;
	PWMA_Duty.PWM4_Duty = 1024;

	PWMx_InitStructure.PWM_Mode    =	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty    = PWMA_Duty.PWM1_Duty;	//PWMռ�ձ�ʱ��, 0~Period
	PWMx_InitStructure.PWM_EnoSelect   = ENO1P | ENO1N;	//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM1, &PWMx_InitStructure);				//��ʼ��PWM1

	PWMx_InitStructure.PWM_Mode    =	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty    = PWMA_Duty.PWM2_Duty;	//PWMռ�ձ�ʱ��, 0~Period
	PWMx_InitStructure.PWM_EnoSelect   = ENO2P | ENO2N;	//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM2, &PWMx_InitStructure);				//��ʼ��PWM2

	PWMx_InitStructure.PWM_Mode    =	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty    = PWMA_Duty.PWM3_Duty;	//PWMռ�ձ�ʱ��, 0~Period
	PWMx_InitStructure.PWM_EnoSelect   = ENO3P | ENO3N;	//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM3, &PWMx_InitStructure);				//��ʼ��PWM3

	PWMx_InitStructure.PWM_Mode    =	CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty    = PWMA_Duty.PWM4_Duty;	//PWMռ�ձ�ʱ��, 0~Period
	PWMx_InitStructure.PWM_EnoSelect   = ENO4P | ENO4N;	//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM4, &PWMx_InitStructure);				//��ʼ��PWM4

	PWMx_InitStructure.PWM_Period   = 2047;							//����ʱ��,   0~65535
	PWMx_InitStructure.PWM_DeadTime = 0;								//��������������, 0~255
	PWMx_InitStructure.PWM_MainOutEnable= ENABLE;				//�����ʹ��, ENABLE,DISABLE
	PWMx_InitStructure.PWM_CEN_Enable   = ENABLE;				//ʹ�ܼ�����, ENABLE,DISABLE
	PWM_Configuration(PWMA, &PWMx_InitStructure);				//��ʼ��PWMͨ�üĴ���,  PWMA,PWMB

	PWM1_USE_P60P61();
	PWM2_USE_P62P63();
	PWM3_USE_P64P65();
	PWM4_USE_P66P67();

	NVIC_PWM_Init(PWMA,DISABLE,Priority_0);
}


