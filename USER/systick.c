#include <stm32f10x.h>
#include <core_cm3.h>

u16 vu16Time;

//函数原型： void fSysTick_Set(unsigned int vuiTime)
//函数功能：
//函数参数：
//函数出口：
//函数调用：
//函数说明：
void fSysTick_Set(unsigned int vuiTime)
{
    if( SysTick_Config(vuiTime *72 ))     //配置错误返回1,max 16777216
    {                          
       //                           
    }
}

void SysTick_Handler(void)
{
	vu16Time ++;
}