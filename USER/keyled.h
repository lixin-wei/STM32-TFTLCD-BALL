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


//�������
#define	cKEY_PORT	GPIOE		//�����ÿ�
#define cKEY_RCCPORT	RCC_APB2Periph_GPIOE
#define	cKEY0_PIN	GPIO_Pin_4	//������Ӧ����
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

//����ԭ�ͣ�void fGPIO_Init(void)
//�������ܣ�		
//����������
//�������ڣ�
//�������ã�
//����˵����
void fGPIO_Init(void);

//����ԭ�ͣ� void fLED_ON(void);
//�������ܣ�
//����������
//�������ڣ�
//�������ã�
//����˵���� 
void fLED_ON(void);

//����ԭ�ͣ� void fLED_OFF(void);
//�������ܣ�
//����������
//�������ڣ�
//�������ã�
//����˵���� 
void fLED_OFF(void);


//����ԭ�ͣ� void fBeep(BitAction vucBeepStat);
//�������ܣ�
//����������
//�������ڣ�
//�������ã�
//����˵���� 
void fBeep(BitAction vucBeepStat);

//����ԭ�ͣ�unsigned char fKEY_RdPin(void)
//�������ܣ�ɨ����̣���ȡ�������ŵ�״̬
//������������
//�������ڣ�0���޼�ֵ��1��2���ֱ��ӦKEY1   KEY2  ;�����Ƕ��ذ��� KEY1 ������KEY2����
//�������ã�
//����˵����������ȥ����ֱ�Ӷ�ȡ����һ�����ŵ�״̬
unsigned char fKEY_RdPin(void);

//����ԭ�ͣ�unsigned char fKEY_GetKeyValue(void)
//�������ܣ�ɨ����̣���ȡ��ֵ  1  2   
//������������
//�������ڣ�0���޼�ֵ��1��2 ���ֱ��ӦKEY1   KEY2  ;�����Ƕ��ذ��� KEY1 ������KEY2����
//�������ã�fKEY_RdPin  ��fDelay(10���뼶��)
//����˵����
unsigned char fKEY_GetKeyValue(void);

//����ԭ�ͣ� BitAction fLightStat(void);
//�������ܣ�
//����������
//�������ڣ�
//�������ã�
//����˵���� 
BitAction fLightStat(void);


#endif
