#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include <stdlib.h>
#include <math.h>
#include "time.h"
#include "keyled.h"
#include "systick.h"
#include "general.h"
#include <stdio.h>


#define SCREEN_WIDTH 250
#define SCREEN_HEIGHT 320
#define EPS 1e-5;
#define FRONT_COLOR WHITE
#define BK_COLOR BLACK
#define random(a,b) ((a)+rand()%((b)-(a)+1))

typedef struct Point {
	float x, y;
}Point;

typedef struct Ball {
	Point pos; float r;
	Point v;
} Ball;

Point PT_add(Point a, Point b) {
	Point t;
	t.x = a.x + b.x;
	t.y = a.y + b.y;
	return t;
}
Point PT_sub(Point a, Point b) {
	Point t;
	t.x = a.x - b.x;
	t.y = a.y - b.y;
	return t;
}
Point PT_mul(Point x, float a) {
	x.x *= a;
	x.y *= a;
	return x;
}
float PT_dot(Point a, Point b) {
	return a.x*b.x + a.y*b.y;
}
Point PT_getUnit(Point pt) {
	float len = sqrt(pt.x*pt.x + pt.y*pt.y);
	pt.x /= len;
	pt.y /= len;
	return pt;
}
int PT_isParallel(Point a, Point b) {
	return fabs(a.x*b.y - b.x*a.y) < EPS;
}
//链表，带头节点
typedef struct Ball_listNode {
	struct Ball_listNode *next;
	Ball *ball;
} Ball_listNode;

Ball_listNode *Ball_listHead;

void Ball_init() {
	Ball_listHead = malloc(sizeof(Ball_listNode));
	Ball_listHead->next = NULL;
}
//链表END

float dis(Point a,  Point b) {
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
int Ball_willCollide(Ball *ball1, Ball *ball2) {
	Point npos1 = PT_add(ball1->pos, ball1->v);
	Point npos2 = PT_add(ball2->pos, ball2->v);
	return dis(npos1, npos2) < ball1->r + ball2->r;
}
Point PT_reflectDir(Point I, Point N) {
	return PT_sub(I, PT_mul(N, 2*PT_dot(I, N)));
}
void Ball_move(Ball* ball) {
	//计算与墙面的碰撞
	Point npos = PT_add(ball->pos, ball->v);
	if(npos.x + ball->r > SCREEN_WIDTH || npos.x - ball->r < 0) {
		fBeep(cBEEP_ON);
		ball->v.x *= -1;
	}
	if(npos.y + ball->r > SCREEN_HEIGHT || npos.y - ball->r < 0) {
		fBeep(cBEEP_ON);
		ball->v.y *= -1;
	}
	//计算球与球之间的碰撞
	Ball_listNode *now = Ball_listHead->next;
	while(now != NULL) {
		Ball* ball1 = ball;
		Ball* ball2 = now->ball;
		if(ball1 == ball2) {
			now = now->next;
			continue;
		}
		//简单起见，假设只会与一个球碰撞
		if(Ball_willCollide(ball1, ball2)) {
			ball1->v = PT_reflectDir(ball1->v, PT_getUnit(PT_sub(ball1->pos, ball2->pos)));
			ball2->v = PT_reflectDir(ball2->v, PT_getUnit(PT_sub(ball2->pos, ball1->pos)));
			fBeep(cBEEP_ON);
			break;
		}
		now = now->next;
	}
	ball->pos = PT_add(ball->pos, ball->v);
}


void Ball_update(Ball* ball) {
	Ball_move(ball);
}

void Ball_draw(Ball *ball, int color) {
	POINT_COLOR = color;
	LCD_Draw_Circle(ball->pos.x, ball->pos.y, ball->r);
	LCD_Draw_Circle(ball->pos.x, ball->pos.y, ball->r - 1);
	LCD_Draw_Circle(ball->pos.x, ball->pos.y, ball->r - 2);
}

void BallList_update() {
	Ball_listNode *now = Ball_listHead->next;
	while(now != NULL) {
		Ball_update(now->ball);
		now = now->next;
	}
}

void BallList_draw(int color) {
	Ball_listNode *now = Ball_listHead->next;
	while(now != NULL) {
		Ball_draw(now->ball, color);
		now = now->next;
	}
}
void BallList_addNewBall(float x, float y, float r, float vx, float vy) {
	Ball *nBall = malloc(sizeof(Ball));
	nBall->pos.x = x; nBall->pos.y = y; nBall->r = r; nBall->v.x = vx; nBall->v.y = vy;
	
	//头部插入
	Ball_listNode *next = Ball_listHead->next;
	Ball_listHead->next = malloc(sizeof(Ball_listNode));
	Ball_listHead->next->next = next;
	Ball_listHead->next->ball = nBall;
}


int main(void) {
	fGPIO_Init(); 
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 
	LCD_Init();
	LCD_Clear(BK_COLOR);
	POINT_COLOR = FRONT_COLOR;

	Ball_init();
	
	//BallList_addNewBall( 50, 50, 10, 1, 0);
	//BallList_addNewBall( 100, 50, 10, -1, 0);
	for(int i=0 ; i<10 ; ++i) {
		BallList_addNewBall(random(30, SCREEN_WIDTH-30), random(30, SCREEN_HEIGHT-30), 10, random(-10, 10)/2.0, random(-10,10)/ 2.0);
	}
	
	while(1) {
		BallList_draw(BK_COLOR);
		BallList_update();
		BallList_draw(FRONT_COLOR);
		fBeep(cBEEP_OFF);
		fDelayUs(200000);
	}
}
 