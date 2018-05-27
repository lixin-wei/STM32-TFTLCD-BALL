#ifndef __MYLCD_H
#define __MYLCD_H

#include "sys.h"
#include "stdlib.h"
//=========================================================================
//���ILI9341������LCD
//�ܾ�  V1   2018.5.1


//����ԭ��-----------------------------------------------------------------
typedef struct 
{
	vu16	LCD_REG;
	vu16	LCD_RAM;
}LCD_TypeDef;

//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=11 A10��Ϊ�������������� 
//ע������ʱSTM32�ڲ�������һλ����! 			    
#define LCD_BASE        ((u32)(0x6C000000 | 0x000007FE))
#define LCD             ((LCD_TypeDef *) LCD_BASE)
//////////////////////////////////////////////////////////////////////////////////


void fLCD_Init(void); 				//��ʼ��LCD 9341

//����ԭ�ͣ� void fLCD_WriteReg(u16 v16RegNumber, u16 v16RegValue)
//�������ܣ� д�Ĵ���ֵ��������д�뵽ָ���Ĵ�����
//��ڲ����� v16RegNumber:�Ĵ����ţ�v16RegValue:д�뵽�Ĵ����е�����
//���ڲ�����
//�������ã�
//����˵����
void fLCD_WriteReg(u16 v16RegNumber, u16 v16RegValue);

//����ԭ�ͣ�void fLCD_WriteRegNumber(u16 v16RegNumber)  
//�������ܣ�д�Ĵ�����  
//��ڲ�����v16RegNumber���Ĵ����� 
//���ڲ�����
//�������ã�
//����˵����
void fLCD_WriteRegNumber(u16 v16RegNumber);

//����ԭ�ͣ� void fLCD_WriteRam(u16 v16RamData)
//�������ܣ� дLCD RAM
//��ڲ����� v16RamData:��д�������
//���ڲ�����
//�������ã� ֮ǰ��Ҫ�ȵ���void fLCD_WriteRegNumber(u16 v16RegNumber)����ָ����д��ļĴ���
//����˵����
void fLCD_WriteRam(u16 v16RamData);


//����ԭ�ͣ�u16 fLCD_ReadReg(u16 v16RegNumber)
//�������ܣ���ȡָ���Ĵ�������
//��ڲ����� v16RegNumber���Ĵ����� 
//���ڲ����� U16���Ĵ�������
//�������ã�
//����˵���� 
u16 fLCD_ReadReg(u16 v16RegNumber);


//����ԭ�ͣ�  u16 fLCD_ReadData(void)
//�������ܣ�  ������
//��ڲ�����  
//���ڲ�����
//�������ã� ֮ǰ��Ҫ�ȵ���void fLCD_WriteRegNumber(u16 v16RegNumber)����ָ������ȡ�ļĴ���
//����˵���� 
u16 fLCD_ReadData(void);


//����ԭ�ͣ�  
//�������ܣ�  
//��ڲ�����  
//���ڲ�����
//�������ã�
//����˵���� 

//����ԭ�ͣ�  
//�������ܣ�  
//��ڲ�����  
//���ڲ�����
//�������ã�
//����˵���� 

//����ԭ�ͣ�  
//�������ܣ�  
//��ڲ�����  
//���ڲ�����
//�������ã�
//����˵���� 

//����ԭ�ͣ�  
//�������ܣ�  
//��ڲ�����  
//���ڲ�����
//�������ã�
//����˵���� 
#endif
