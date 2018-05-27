#include "keyled.h"
#include "general.h"

//================================================================================================
//����ԭ�ͣ�void fGPIO_Init(void)
//�������ܣ���ʼ��ϵͳ�õ�GPIO��
//			��ʼ��LED������ڣ�50MHz ,���췽ʽ
//			LED1:PORTA.1   LED2��PORTA.2  LED3��PORTA.3  LED4:PORTA.4  LED5:PORTA.5  LED6:PORTA.6
//			��ʼ��KEY������ڣ���������
//			KEY1��PORTB.1  KEY2��PORTB.2  KEY3��PORTB.3
//�����������ޣ��漰��GPIOA 1-6��GPIOB1-3��������������
//�������ڣ������GPIO��ģʽ
//�������ã���
//����˵����
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

//����ԭ�ͣ� void fLED_ON(void);
//�������ܣ�
//����������
//�������ڣ�
//�������ã�
//����˵���� 
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

//����ԭ�ͣ� void fBeep(BitAction vucBeepStat);
//�������ܣ�
//����������
//�������ڣ�
//�������ã�
//����˵���� 
void fBeep(BitAction vucBeepStat)
{
	GPIO_WriteBit(cOUT1_PORT, cBEEP_PIN,vucBeepStat);

}
//����ԭ�ͣ�unsigned char fKEY_RdPin(void)
//�������ܣ�ɨ����̣���ȡ�������ŵ�״̬
//������������
//�������ڣ�0���޼�ֵ��1��2���ֱ��ӦKEY1   KEY2  ;�����Ƕ��ذ��� KEY1 ������KEY2����
//�������ã�
//����˵����������ȥ����ֱ�Ӷ�ȡ����һ�����ŵ�״̬
unsigned char fKEY_RdPin(void)
{
	unsigned int vuiKeyPortValue;
	if ( ! cKEY_ON)		//����Ϊ�͵�ƽ��
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

//����ԭ�ͣ�unsigned char fKEY_GetKeyValue(void)
//�������ܣ�ɨ����̣���ȡ��ֵ  1  2  
//������������
//�������ڣ�0���޼�ֵ��1��2���ֱ��ӦKEY1   KEY2  ;�����Ƕ��ذ��� KEY1 ������KEY2����
//�������ã�fKEY_RdPin  ��fDelay(10���뼶��)
//����˵����
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

//����ԭ�ͣ� BitAction fLightStat(void);
//�������ܣ�
//����������
//�������ڣ�
//�������ã�
//����˵���� 
BitAction fLightStat(void)
{
	return (BitAction )GPIO_ReadInputDataBit(cSENSOR_PORT,cSENSOR_PIN); 
}
