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
void fNewPos(void);   //������һ������꼰�˶�����
void fCreatPos(void); //��������㼰�˶�����
void fPaintBall(u16 v16Color);//��vfPosX,vfPosY�㻭v16Color��c8R�뾶��Բ
//-------------------------------------
static float vfDx,vfDy,vfDTmp;//x,y����ı���
static float vfPosX ,vfPosY;//x,y����ֵ

//===============================================================
 int main(void)
 {	   

	int viDirX,viDirY;

	//��ȡ�����
	 
	fGPIO_Init(); 
	fCreatPos(); //������ʼ��λ�ü��˶�����
	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 
	LCD_Init();
	LCD_Clear(BLACK);
	POINT_COLOR = WHITE;
	 
	LCD_DrawRectangle(cMINX,cMINY,cMAXX,cMAXY);
	fPaintBall(cBALLCOLOR);
	while(1){
		fPaintBall(cBACKCOLOR);//����֮ǰԲ
		fNewPos();//�����µ�λ�ü��˶�����
		fPaintBall(cBALLCOLOR);//��λ�û�Բ
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
//�������ƣ�void fNewPos(void)
//�������ܣ������µ�λ�õ�����
//��ڲ�����vfPosX ��ǰ x,vfPosY��ǰ y ,vfDx x����仯��,vfDy y����仯��
//���ڲ�����vfPosX ��λ�õ�x,vfPosY��λ�õ�y ,vfDx x����仯��,vfDy y����仯�
//�������ã�
//����˵����
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


//�������ƣ�void fCreatPos(void)
//�������ܣ�����һ�������(40,40)-(200-280)֮���һ����
//��ڲ�����
//���ڲ�����vfPosX x����,vfPosY y����,vfDx x����仯��,vfDy y����仯��
//�������ã�srand,rand;
//����˵������α������������ݰ���ʱ�������������
void fCreatPos(void)
{
	fSysTick_Set(1) ; //����1us��ʱ
	while(fKEY_GetKeyValue() == 0);//�ȴ�����
	while(fKEY_RdPin() != 0) ;//�ȴ����ͷ�
	srand(vu16Time);//vu16Time��SysTick_Handler�� ��1����Ϊ���������
	vfPosX  =  rand() % 159 + 41 ;//�õ��������Xֵ
	srand(vu16Time);
	vfPosY  =  rand() % 239 + 41 ;//�õ��������Yֵ
	srand(vu16Time);
	vfDx =  rand() % 21 - 10; //�õ����X����ı���
	srand(vu16Time);
	vfDy =  rand() % 21 - 10; //�õ����Y����ı���
	fSysTick_Set(100000) ; 
	//���´���ʹ��  vfDy = vfDy/vfDx��vfDx = 1 ���� -1��  
	//����X����ÿ�α仯��Ϊ 1��ʹ���ƶ�ƽ��
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

//�������ƣ�void fPaintBall(u16 v16Color)
//�������ܣ��ڵ�ǰλ�ã�vfPosX,vfPosY,�뾶c8R ����v16Color��ɫ��һ��Բ
//��ڲ�����vfPosX ��ǰ x,vfPosY��ǰ y ,�뾶c8R, v16Color��ɫ
//���ڲ�����
//�������ã�void fNewPos(void)  ������һ������
//			void fCreatPos(void) ������ʼ������
//����˵����
void fPaintBall(u16 v16Color)
{
	POINT_COLOR = v16Color;
	LCD_Draw_Circle(vfPosX,vfPosY,c8R);
	LCD_Draw_Circle(vfPosX,vfPosY,c8R-1);
	LCD_Draw_Circle(vfPosX,vfPosY,c8R-2);
}