#ifndef __MYLCD_H
#define __MYLCD_H

#include "sys.h"
#include "stdlib.h"
//=========================================================================
//针对ILI9341驱动的LCD
//周炯  V1   2018.5.1


//函数原型-----------------------------------------------------------------
typedef struct 
{
	vu16	LCD_REG;
	vu16	LCD_RAM;
}LCD_TypeDef;

//使用NOR/SRAM的 Bank1.sector4,地址位HADDR[27,26]=11 A10作为数据命令区分线 
//注意设置时STM32内部会右移一位对其! 			    
#define LCD_BASE        ((u32)(0x6C000000 | 0x000007FE))
#define LCD             ((LCD_TypeDef *) LCD_BASE)
//////////////////////////////////////////////////////////////////////////////////


void fLCD_Init(void); 				//初始化LCD 9341

//函数原型： void fLCD_WriteReg(u16 v16RegNumber, u16 v16RegValue)
//函数功能： 写寄存器值，将数据写入到指定寄存器中
//入口参数： v16RegNumber:寄存器号，v16RegValue:写入到寄存器中的数据
//出口参数：
//函数调用：
//其他说明：
void fLCD_WriteReg(u16 v16RegNumber, u16 v16RegValue);

//函数原型：void fLCD_WriteRegNumber(u16 v16RegNumber)  
//函数功能：写寄存器号  
//入口参数：v16RegNumber：寄存器号 
//出口参数：
//函数调用：
//其他说明：
void fLCD_WriteRegNumber(u16 v16RegNumber);

//函数原型： void fLCD_WriteRam(u16 v16RamData)
//函数功能： 写LCD RAM
//入口参数： v16RamData:将写入的数据
//出口参数：
//函数调用： 之前需要先调用void fLCD_WriteRegNumber(u16 v16RegNumber)，来指定待写入的寄存器
//其他说明：
void fLCD_WriteRam(u16 v16RamData);


//函数原型：u16 fLCD_ReadReg(u16 v16RegNumber)
//函数功能：读取指定寄存器内容
//入口参数： v16RegNumber：寄存器号 
//出口参数： U16，寄存器内容
//函数调用：
//其他说明： 
u16 fLCD_ReadReg(u16 v16RegNumber);


//函数原型：  u16 fLCD_ReadData(void)
//函数功能：  读数据
//入口参数：  
//出口参数：
//函数调用： 之前需要先调用void fLCD_WriteRegNumber(u16 v16RegNumber)，来指定待读取的寄存器
//其他说明： 
u16 fLCD_ReadData(void);


//函数原型：  
//函数功能：  
//入口参数：  
//出口参数：
//函数调用：
//其他说明： 

//函数原型：  
//函数功能：  
//入口参数：  
//出口参数：
//函数调用：
//其他说明： 

//函数原型：  
//函数功能：  
//入口参数：  
//出口参数：
//函数调用：
//其他说明： 

//函数原型：  
//函数功能：  
//入口参数：  
//出口参数：
//函数调用：
//其他说明： 
#endif
