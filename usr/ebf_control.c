#include "ebf_control.h"

void	controlbeep(void)
{

	if( low_f & (!high_f) & six_f & five_f & four_f & three_f & two_f & one_f) //diyin sol
		{
		PWM_config(Sound_Fre[0][4]);
		printf("diyin sol\r\n");
		}
	if( low_f & (!high_f) & six_f & five_f & four_f & three_f & two_f & (!one_f)) //diyin la
		{
		PWM_config(Sound_Fre[0][5]);
		printf("diyin 2\r\n");
		}
	if( low_f & (!high_f) & six_f & five_f & four_f & three_f & (!two_f) & (!one_f)) //diyin si
		{
		PWM_config(Sound_Fre[0][6]);
		printf("diyin 3\r\n");
		}
	
	if( (!low_f) & (!high_f) & six_f & five_f & four_f & (!three_f) & (!two_f) & (!one_f)) //zhongyin do
		{
		PWM_config(Sound_Fre[1][0]);
		printf("yin 1\r\n");
		}
	if( (!low_f) & (!high_f) & six_f & five_f & (!four_f) & (!three_f) & (!two_f) & (!one_f)) //zhongyin re
		{
		PWM_config(Sound_Fre[1][1]);
		printf("yin 2\r\n");
		}
	if( (!low_f) & (!high_f) & six_f & (!five_f) & (!four_f) & (!three_f) & (!two_f) & (!one_f)) //zhongyin mi
		{
		PWM_config(Sound_Fre[1][2]);  
		printf("yin 3\r\n");
		}
	if( (!low_f) & (!high_f) & (!six_f) & five_f & four_f & (!three_f) & (!two_f) & (!one_f)) //zhongyin fa
		{
		PWM_config(Sound_Fre[1][3]);  
		printf("yin 4\r\n");
		}
	if( (!low_f) & (!high_f) & six_f & five_f & four_f & three_f & two_f & one_f) //zhongyin sol
		{
		PWM_config(Sound_Fre[1][4]);
		printf("yin 5\r\n");
		}
	if( (!low_f) & (!high_f) & six_f & five_f & four_f & three_f & two_f & (!one_f)) //zhongyin la
		{
		PWM_config(Sound_Fre[0][5]);
		printf("yin 6\r\n");
		}
	if( (!low_f) & (!high_f) & six_f & five_f & four_f & three_f & (!two_f) & (!one_f)) //zhongyin si
		{
		PWM_config(Sound_Fre[0][6]);
		printf("yin 7\r\n");
		}
	
	if( (!low_f) & high_f & six_f & five_f & four_f & (!three_f) & (!two_f) & (!one_f)) //gaoyiin do
		{
		PWM_config(Sound_Fre[2][0]);
		printf("gaoyin 1\r\n");
		}
	if( (!low_f) & high_f & six_f & five_f & (!four_f) & (!three_f) & (!two_f) & (!one_f)) //gaoyiin re
		{
		PWM_config(Sound_Fre[2][1]);
		printf("gaoyin 2\r\n");
		}
	if( (!low_f) & high_f & six_f & (!five_f) & (!four_f) & (!three_f) & (!two_f) & (!one_f)) //gaoyiin mi
		{
		PWM_config(Sound_Fre[2][2]);  
		printf("gaoyin 3\r\n");
		}
	if( (!low_f) & high_f & (!six_f) & five_f & four_f & (!three_f) & (!two_f) & one_f) //gaoyiin fa
		{
		PWM_config(Sound_Fre[2][3]);  
		printf("gaoyin 4\r\n");
		}
	if( (!low_f) & high_f & six_f & five_f & four_f & three_f & two_f & one_f) //gaoyiin sol
		{
		PWM_config(Sound_Fre[2][4]);
		printf("gaoyin 5\r\n");
		}
	if( (!low_f) & high_f & six_f & five_f & (!four_f) & three_f & two_f & (!one_f)) //gaoyiin la
		{
		PWM_config(Sound_Fre[2][5]);
		printf("gaoyin 6\r\n");
		}
	if( (!low_f) & high_f & six_f & (!five_f) & four_f & three_f & (!two_f) & one_f) //gaoyiin si
		{
		PWM_config(Sound_Fre[2][6]);
		printf("gaoyin 7\r\n");
		}
}