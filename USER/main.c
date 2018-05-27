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
void fNewPos(void);   //Éú³ÉÏÂÒ»µãµÄ×ø±ê¼°ÔË¶¯·½Ïò
void fCreatPos(void); //´´½¨Ëæ»úµã¼°ÔË¶¯·½Ïò
void fPaintBall(u16 v16Color);//ÔÚvfPosX,vfPosYµã»­v16Color£¬c8R°ë¾¶µÄÔ²
//-------------------------------------
static float vfDx,vfDy,vfDTmp;//x,y·½Ïò¸Ä±äÁ¿
static float vfPosX ,vfPosY;//x,y×ø±êÖµ

//===============================================================
 int main(void)
 {	   

	int viDirX,viDirY;

	//»ñÈ¡Ëæ»úÊý
	 
	fGPIO_Init(); 
	fCreatPos(); //´´½¨ÆðÊ¼µãÎ»ÖÃ¼°ÔË¶¯·½Ïò
	 
	delay_init();	    	 //ÑÓÊ±º¯Êý³õÊ¼»¯	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //ÉèÖÃNVICÖÐ¶Ï·Ö×é2:2Î»ÇÀÕ¼ÓÅÏÈ¼¶£¬2Î»ÏìÓ¦ÓÅÏÈ¼¶ 
	LCD_Init();
	LCD_Clear(BLACK);
	POINT_COLOR = WHITE;
	 
	LCD_DrawRectangle(cMINX,cMINY,cMAXX,cMAXY);
	fPaintBall(cBALLCOLOR);
	while(1){
		fPaintBall(cBACKCOLOR);//²Á³ýÖ®Ç°Ô²
		fNewPos();//Éú³ÉÐÂµãÎ»ÖÃ¼°ÔË¶¯·½Ïò
		fPaintBall(cBALLCOLOR);//ÐÂÎ»ÖÃ»­Ô²
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
//º¯ÊýÃû³Æ£ºvoid fNewPos(void)
//º¯Êý¹¦ÄÜ£ºÉú³ÉÐÂµÄÎ»ÖÃµã×ø±ê
//Èë¿Ú²ÎÊý£ºvfPosX µ±Ç° x,vfPosYµ±Ç° y ,vfDx x·½Ïò±ä»¯Á¿,vfDy y·½Ïò±ä»¯Á¿
//³ö¿Ú²ÎÊý£ºvfPosX ÐÂÎ»ÖÃµÄx,vfPosYÐÂÎ»ÖÃµÄy ,vfDx x·½Ïò±ä»¯Á¿,vfDy y·½Ïò±ä»¯Á
//º¯Êýµ÷ÓÃ£º
//º¯ÊýËµÃ÷£º
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


//º¯ÊýÃû³Æ£ºvoid fCreatPos(void)
//º¯Êý¹¦ÄÜ£º´´½¨Ò»¸öËæ»úµã(40,40)-(200-280)Ö®¼äµÄÒ»¸öµã
//Èë¿Ú²ÎÊý£º
//³ö¿Ú²ÎÊý£ºvfPosX x×ø±ê,vfPosY y×ø±ê,vfDx x·½Ïò±ä»¯Á¿,vfDy y·½Ïò±ä»¯Á¿
//º¯Êýµ÷ÓÃ£ºsrand,rand;
//º¯ÊýËµÃ÷£ºÓÃÎ±Ëæ»úº¯Êý£¬¸ù¾Ý°´¼üÊ±¼äÀ´´´½¨Ëæ»úµã
void fCreatPos(void)
{
	fSysTick_Set(1) ; //Æô¶¯1us¶¨Ê±
	while(fKEY_GetKeyValue() == 0);//µÈ´ý°´¼ü
	while(fKEY_RdPin() != 0) ;//µÈ´ý¼üÊÍ·Å
	srand(vu16Time);//vu16TimeÔÚSysTick_HandlerÖÐ ¼Ó1¡£×÷ÎªËæ»úÊýÖÖ×Ó
	vfPosX  =  rand() % 159 + 41 ;//µÃµ½Ëæ»ú×ø±êXÖµ
	srand(vu16Time);
	vfPosY  =  rand() % 239 + 41 ;//µÃµ½Ëæ»ú×ø±êYÖµ
	srand(vu16Time);
	vfDx =  rand() % 21 - 10; //µÃµ½Ëæ»úX·½Ïò¸Ä±äÁ¿
	srand(vu16Time);
	vfDy =  rand() % 21 - 10; //µÃµ½Ëæ»úY·½Ïò¸Ä±äÁ¿
	fSysTick_Set(100000) ; 
	//ÒÔÏÂ´¦ÀíÊ¹µÃ  vfDy = vfDy/vfDx£¬vfDx = 1 »òÕß -1£¬  
	//ÕâÑùX·½ÏòÃ¿´Î±ä»¯Á¿Îª 1£¬Ê¹µÃÒÆ¶¯Æ½»¬
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

//º¯ÊýÃû³Æ£ºvoid fPaintBall(u16 v16Color)
//º¯Êý¹¦ÄÜ£ºÔÚµ±Ç°Î»ÖÃ£¨vfPosX,vfPosY,°ë¾¶c8R £©ÓÃv16ColorÑÕÉ«»­Ò»¸öÔ²
//Èë¿Ú²ÎÊý£ºvfPosX µ±Ç° x,vfPosYµ±Ç° y ,°ë¾¶c8R, v16ColorÑÕÉ«
//³ö¿Ú²ÎÊý£º
//º¯Êýµ÷ÓÃ£ºvoid fNewPos(void)  Éú³ÉÏÂÒ»µã×ø±ê
//			void fCreatPos(void) ´´½¨ÆðÊ¼µã×ø±ê
//º¯ÊýËµÃ÷£º
void fPaintBall(u16 v16Color)
{
	POINT_COLOR = v16Color;
	LCD_Draw_Circle(vfPosX,vfPosY,c8R);
	LCD_Draw_Circle(vfPosX,vfPosY,c8R-1);
	LCD_Draw_Circle(vfPosX,vfPosY,c8R-2);
}