#include <stm32f10x.h>
#include <core_cm3.h>

u16 vu16Time;

//����ԭ�ͣ� void fSysTick_Set(unsigned int vuiTime)
//�������ܣ�
//����������
//�������ڣ�
//�������ã�
//����˵����
void fSysTick_Set(unsigned int vuiTime)
{
    if( SysTick_Config(vuiTime *72 ))     //���ô��󷵻�1,max 16777216
    {                          
       //                           
    }
}

void SysTick_Handler(void)
{
	vu16Time ++;
}