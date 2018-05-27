#include "keyled.h"
#include "general.h"

//================================================================================================
//函数原型：void fGPIO_Init(void)
//函数功能：初始化系统用到GPIO口
//			初始化LED：输出口，50MHz ,推挽方式
//			LED1:PORTA.1   LED2：PORTA.2  LED3：PORTA.3  LED4:PORTA.4  LED5:PORTA.5  LED6:PORTA.6
//			初始化KEY：输入口，上拉输入
//			KEY1：PORTB.1  KEY2：PORTB.2  KEY3：PORTB.3
//函数参数：无，涉及到GPIOA 1-6，GPIOB1-3，具体如上描述
//函数出口：具体的GPIO口模式
//函数调用：无
//函数说明：
void fGPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(cOUT_RCCPORT , ENABLE);	
	GPIO_InitStructure.GPIO_Pin = cLED0_PIN | cBEEP_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(cOUT1_PORT, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = cLED1_PIN;
	GPIO_Init(cOUT2_PORT, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(cKEY_RCCPORT , ENABLE);	
	GPIO_InitStructure.GPIO_Pin = cKEY0_PIN | cKEY1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(cKEY_PORT, &GPIO_InitStructure);	
	
	RCC_APB2PeriphClockCmd(cSENSOR_RCCPORT , ENABLE);	
	GPIO_InitStructure.GPIO_Pin = cSENSOR_PIN ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(cSENSOR_PORT, &GPIO_InitStructure);	
}

//函数原型： void fLED_ON(void);
//函数功能：
//函数参数：
//函数出口：
//函数调用：
//函数说明： 
void fLED_ON(void)
{
	GPIO_WriteBit(cOUT1_PORT, cLED0_PIN,cLED_ON);
	GPIO_WriteBit(cOUT2_PORT, cLED1_PIN,cLED_ON);	
}

void fLED_OFF(void)
{
	GPIO_WriteBit(cOUT1_PORT, cLED0_PIN,cLED_OFF);
	GPIO_WriteBit(cOUT2_PORT, cLED1_PIN,cLED_OFF);	
}

//函数原型： void fBeep(BitAction vucBeepStat);
//函数功能：
//函数参数：
//函数出口：
//函数调用：
//函数说明： 
void fBeep(BitAction vucBeepStat)
{
	GPIO_WriteBit(cOUT1_PORT, cBEEP_PIN,vucBeepStat);

}
//函数原型：unsigned char fKEY_RdPin(void)
//函数功能：扫描键盘，读取按键引脚的状态
//函数参数：无
//函数出口：0：无键值，1、2，分别对应KEY1   KEY2  ;不考虑多重按键 KEY1 优先于KEY2……
//函数调用：
//函数说明：不考虑去抖，直接读取的是一次引脚的状态
unsigned char fKEY_RdPin(void)
{
	unsigned int vuiKeyPortValue;
	if ( ! cKEY_ON)		//键入为低电平则
	{
		vuiKeyPortValue = GPIO_ReadInputData(cKEY_PORT);
		if (!( vuiKeyPortValue & cKEY0_IN )) return 1;
		if (!( vuiKeyPortValue & cKEY1_IN )) return 2;
	}
	else
	{
		vuiKeyPortValue = GPIO_ReadInputData(cKEY_PORT);
		if ( vuiKeyPortValue & cKEY0_IN ) return 1;
		if ( vuiKeyPortValue & cKEY1_IN ) return 2;	
	}
	return 0;
}

//函数原型：unsigned char fKEY_GetKeyValue(void)
//函数功能：扫描键盘，获取键值  1  2  
//函数参数：无
//函数出口：0：无键值，1、2，分别对应KEY1   KEY2  ;不考虑多重按键 KEY1 优先于KEY2……
//函数调用：fKEY_RdPin  ，fDelay(10毫秒级别)
//函数说明：
unsigned char fKEY_GetKeyValue(void)
{	unsigned char vucKeyTmp;
	
	vucKeyTmp = fKEY_RdPin();
	fDelayUs(0xffff);
	if (vucKeyTmp == fKEY_RdPin() ) 
	{
		return vucKeyTmp;
	}
	return 0;
}

//函数原型： BitAction fLightStat(void);
//函数功能：
//函数参数：
//函数出口：
//函数调用：
//函数说明： 
BitAction fLightStat(void)
{
	return (BitAction )GPIO_ReadInputDataBit(cSENSOR_PORT,cSENSOR_PIN); 
}
