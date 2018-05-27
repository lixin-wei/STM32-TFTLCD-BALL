#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include <stdlib.h>
#include "time.h"
#include "keyled.h"
#include "systick.h"
#include "general.h"

#define cBACKCOLOR BLACK
#define cBALLCOLOR RED
#define cMINX 31
#define cMINY 31
#define cMAXX 200
#define cMAXY 300
const u8 c8R = 20;
const float EPS = 1e-3;

extern u16 vu16Time;
void fNewPos(void);   //生成下一点的坐标及运动方向
void fCreatPos(void); //创建随机点及运动方向
void fPaintBall(u16 v16Color);//在vfPosX,vfPosY点画v16Color，c8R半径的圆
//-------------------------------------
static float vfDx,vfDy,vfDTmp;//x,y方向改变量
static float vfPosX ,vfPosY;//x,y坐标值

//===============================================================
 int main(void)
 {	   

	int viDirX,viDirY;

	//获取随机数
	 
	fGPIO_Init(); 
	fCreatPos(); //创建起始点位置及运动方向
	 
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 
	LCD_Init();
	LCD_Clear(BLACK);
	POINT_COLOR = WHITE;
	 
	LCD_DrawRectangle(cMINX,cMINY,cMAXX,cMAXY);
	fPaintBall(cBALLCOLOR);
	while(1){
		fPaintBall(cBACKCOLOR);//擦除之前圆
		fNewPos();//生成新点位置及运动方向
		fPaintBall(cBALLCOLOR);//新位置画圆
		if(( vfPosX == cMAXX || vfPosX == cMINX ) || ( vfPosY == cMAXY || vfPosY == cMINY ) )
		{
			//fBeep(cBEEP_ON);
		}
		else
		{
			fBeep(cBEEP_OFF);
		}
		fDelayUs(10000);
	}
}
 

//================================================================
//函数名称：void fNewPos(void)
//函数功能：生成新的位置点坐标
//入口参数：vfPosX 当前 x,vfPosY当前 y ,vfDx x方向变化量,vfDy y方向变化量
//出口参数：vfPosX 新位置的x,vfPosY新位置的y ,vfDx x方向变化量,vfDy y方向变化�
//函数调用：
//函数说明：
void fNewPos(void)
{
		float nPosx = vfPosX + vfDx;
		float nPosy = vfPosY + vfDy;
		if(nPosx + c8R >= cMAXX - EPS || nPosx - c8R <= cMINX + EPS) {
			vfDx *= -1;
		}
		if(nPosy + c8R >= cMAXY - EPS || nPosy - c8R <= cMINY + EPS) {
			vfDy *= -1;
		}
		vfPosX = vfPosX + vfDx ;
		vfPosY = vfPosY + vfDy ;
} 


//函数名称：void fCreatPos(void)
//函数功能：创建一个随机点(40,40)-(200-280)之间的一个点
//入口参数：
//出口参数：vfPosX x坐标,vfPosY y坐标,vfDx x方向变化量,vfDy y方向变化量
//函数调用：srand,rand;
//函数说明：用伪随机函数，根据按键时间来创建随机点
void fCreatPos(void)
{
	fSysTick_Set(1) ; //启动1us定时
	while(fKEY_GetKeyValue() == 0);//等待按键
	while(fKEY_RdPin() != 0) ;//等待键释放
	srand(vu16Time);//vu16Time在SysTick_Handler中 加1。作为随机数种子
	vfPosX  =  rand() % 159 + 41 ;//得到随机坐标X值
	srand(vu16Time);
	vfPosY  =  rand() % 239 + 41 ;//得到随机坐标Y值
	srand(vu16Time);
	vfDx =  rand() % 21 - 10; //得到随机X方向改变量
	srand(vu16Time);
	vfDy =  rand() % 21 - 10; //得到随机Y方向改变量
	fSysTick_Set(100000) ; 
	//以下处理使得  vfDy = vfDy/vfDx，vfDx = 1 或者 -1，  
	//这样X方向每次变化量为 1，使得移动平滑
	vfDTmp = vfDx ;
    if (( vfDx == 0 ) && (vfDy == 0)) 
	{
		vfDx = 1;
	}
	else
	{
		if(vfDTmp > 0 )
		{
			vfDx = 1; 
			vfDy = vfDy / vfDTmp ;
		}
		else
		{
			if(vfDTmp < 0 )
			{
				vfDx = -1 ; 
				vfDy = (-1) * vfDy / vfDTmp ;
			}
		}
	}
}

//函数名称：void fPaintBall(u16 v16Color)
//函数功能：在当前位置（vfPosX,vfPosY,半径c8R ）用v16Color颜色画一个圆
//入口参数：vfPosX 当前 x,vfPosY当前 y ,半径c8R, v16Color颜色
//出口参数：
//函数调用：void fNewPos(void)  生成下一点坐标
//			void fCreatPos(void) 创建起始点坐标
//函数说明：
void fPaintBall(u16 v16Color)
{
	POINT_COLOR = v16Color;
	LCD_Draw_Circle(vfPosX,vfPosY,c8R);
	LCD_Draw_Circle(vfPosX,vfPosY,c8R-1);
	LCD_Draw_Circle(vfPosX,vfPosY,c8R-2);
}