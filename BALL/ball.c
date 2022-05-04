/*********************************************************************************************************
** Author:		             	Vincenzo Mezzela
** Creation date:           17/12/2021
*********************************************************************************************************/

#include "ball.h"
#include "game.h"
#include "../GLCD/glcd.h"


#define WIDTH 5
#define HALFWIDTH 2

typedef struct {
		int16_t pos_x;
		int16_t pos_y;
		int16_t vel_x;
		int16_t vel_y;
}ball_t ;


ball_t ball;
int16_t old_x;
int16_t old_y;


/*******************************************************************************
* Function Name  : BALL_init
* Description    : Set internal variables.
* Input          : - posx : pos_x of the ball
									 - posy : pos_y of the ball
									 - velx : vel_x of the ball
									 - vely : vel_y of the ball
									 - color :	color of the ball
* Output         : None
* Return         : None
* Attention		 	 : None
*******************************************************************************/
void	BALL_init(int16_t posx,int16_t posy,int16_t velx,int16_t vely){
	ball.pos_x = posx;
	ball.pos_y = posy;
	ball.vel_x = velx;
	ball.vel_y = vely;
	old_x = posx;
	old_y = posy;
	
}

/******************************************************************************
 GET & SET FUNCTIONS 
******************************************************************************/
int16_t BALL_get_posx(void){return ball.pos_x;}
int16_t BALL_get_posy(void){return ball.pos_y;}
int16_t BALL_get_velx(void){return ball.vel_x;}
int16_t BALL_get_vely(void){return ball.vel_y;}
void BALL_set_velx(int16_t velx){ball.vel_x = velx;}
void BALL_set_vely(int16_t vely){ball.vel_y = vely;}
void BALL_set_posy(int16_t posy){ball.pos_y = posy;}
void BALL_set_posx(int16_t posx){ball.pos_x = posx;}
/*******************************************************************************
END GET & SET FUNCTIONS
********************************************************************************/


/*******************************************************************************
* Function Name  : BALL_Draw
* Description    : Draw the ball.
* Input          : None
* Output         : None
* Return         : None
* Attention		 	 : None
*******************************************************************************/

void BALL_Draw(void){
	int8_t i;
	
	// CHECK THE BORDER
	if(ball.pos_x < 3) ball.pos_x = 3;
	if(ball.pos_x > MAX_X - 2) ball.pos_x = MAX_X - 2;
	if(ball.pos_y < 3) ball.pos_y = 3;
	if(ball.pos_y > MAX_Y - 2) ball.pos_y = MAX_Y - 2;
	
	for(i = -2; i< WIDTH-2 ; i++){
		LCD_DrawLine(ball.pos_x - HALFWIDTH,ball.pos_y+i,ball.pos_x + HALFWIDTH ,ball.pos_y+i,BALL_COLOR);
	}
}

/*******************************************************************************
* Function Name  : BALL_Move
* Description    : Move the ball.
* Input          : None
* Output         : None
* Return         : None
* Attention		 	 : None
*******************************************************************************/

void BALL_Move(int16_t x, int16_t y){
	int8_t i;
	
	// CHECK THE BORDER
	if(x < 2) x = 2;
	if(x >= MAX_X - 2) x = MAX_X - 2;
	if(y < 2) y = 2;
	if(y >= MAX_Y - 2) y = MAX_Y - 2;
	
	
	
	for(i = -2 ; i< WIDTH - 2 ; i++){
		LCD_DrawLine(old_x - HALFWIDTH,old_y+i,old_x + HALFWIDTH ,old_y+i,BACKGROUND_COLOR);
	}
	
	//IF THE BALL PASS OVER THE SCORE TEXT
	if(ball.pos_y > 140 && ball.pos_y < 160 && (ball.pos_x < 20 || ball.pos_x > 210 )) GAME_Draw_score(White);
	
	for(i = -2; i< WIDTH - 2; i++){
		LCD_DrawLine(x - HALFWIDTH,y+i,x + HALFWIDTH ,y+i,BALL_COLOR);
	}
	
	
	ball.pos_x = x;
	ball.pos_y = y;
	old_x = x;
	old_y = y;
}

void BALL_delete(void){
	int i ;
	
	for(i = -2; i< WIDTH-2 ; i++){
		LCD_DrawLine(ball.pos_x - HALFWIDTH,ball.pos_y+i,ball.pos_x + HALFWIDTH ,ball.pos_y+i,BACKGROUND_COLOR);
	}
}
