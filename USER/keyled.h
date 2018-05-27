#ifndef __KEYLED
#define __KEYLED

#include <stm32f10x.h>

//LED0   		PORTB.5
//LED1	 		PORTE.5
//BEEP			PORTB.8

//KEY0			PORTE.4
//KEY1			PORTE.3
//LIGHT_SENSOR	PORTF.8

#define	cOUT1_PORT		GPIOB
#define cOUT2_PORT		GPIOE
#define cOUT_RCCPORT	( RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE )
#define	cLED0_PIN	GPIO_Pin_5
#define	cLED1_PIN	GPIO_Pin_5
#define	cBEEP_PIN	GPIO_Pin_8

#define cBEEP_ON	(BitAction)1
#define	cBEEP_OFF	(BitAction)0
#define	cLED_ON		(BitAction)0
#define	cLED_OFF	(BitAction)1


//按键相关
#define	cKEY_PORT	GPIOE		//按键用口
#define cKEY_RCCPORT	RCC_APB2Periph_GPIOE
#define	cKEY0_PIN	GPIO_Pin_4	//按键对应引脚
#define	cKEY1_PIN	GPIO_Pin_3

#define cSENSOR_PORT	GPIOF
#define cSENSOR_RCCPORT	RCC_APB2Periph_GPIOF
#define cSENSOR_PIN		GPIO_Pin_8
#define cKEY0_IN		(1 << 4 )
#define cKEY1_IN		(1 << 3 )

#define cKEY_ON		0
#define	cKEY_OFF	1
#define	cLIGHT_ON	0
#define	cLIGHT_OFF	1

//函数原型：void fGPIO_Init(void)
//函数功能：		
//函数参数：
//函数出口：
//函数调用：
//函数说明：
void fGPIO_Init(void);

//函数原型： void fLED_ON(void);
//函数功能：
//函数参数：
//函数出口：
//函数调用：
//函数说明： 
void fLED_ON(void);

//函数原型： void fLED_OFF(void);
//函数功能：
//函数参数：
//函数出口：
//函数调用：
//函数说明： 
void fLED_OFF(void);


//函数原型： void fBeep(BitAction vucBeepStat);
//函数功能：
//函数参数：
//函数出口：
//函数调用：
//函数说明： 
void fBeep(BitAction vucBeepStat);

//函数原型：unsigned char fKEY_RdPin(void)
//函数功能：扫描键盘，读取按键引脚的状态
//函数参数：无
//函数出口：0：无键值，1、2，分别对应KEY1   KEY2  ;不考虑多重按键 KEY1 优先于KEY2……
//函数调用：
//函数说明：不考虑去抖，直接读取的是一次引脚的状态
unsigned char fKEY_RdPin(void);

//函数原型：unsigned char fKEY_GetKeyValue(void)
//函数功能：扫描键盘，获取键值  1  2   
//函数参数：无
//函数出口：0：无键值，1、2 ，分别对应KEY1   KEY2  ;不考虑多重按键 KEY1 优先于KEY2……
//函数调用：fKEY_RdPin  ，fDelay(10毫秒级别)
//函数说明：
unsigned char fKEY_GetKeyValue(void);

//函数原型： BitAction fLightStat(void);
//函数功能：
//函数参数：
//函数出口：
//函数调用：
//函数说明： 
BitAction fLightStat(void);


#endif
