/*********************************************************************************************************
** Author:		             	Vincenzo Mezzela
** Creation date:           17/12/2021
*********************************************************************************************************/

#include "game.h"
#include "../TIMER/timer.h"
#include "../GLCD/GLCD.h"
#include "../PADDLE/paddle.h"
#include "../BALL/ball.h"
#include <stdio.h>

#define RESTART_STRING "PRESS INT0 TO RESET THE GAME"
#define WIN_STRING "YOU WIN"
#define LOSE_STRING "YOU LOSE"
#define START_STRING "PRESS KEY1 TO START THE GAME"
#define PAUSE_STRING1 "GAME IN PAUSE"
#define PAUSE_STRING2 "PRESS KEY1 TO RESUME"

//INIIAL POSITION & VELOCITY OF THE BALL
#define X0 233
#define Y0 160
#define VX0	5
#define VY0	5

enum border{none,up,down,left,right};



static uint8_t myscore;
static uint8_t pcscore;
static int game_status;


/*******************************************************************************
 SOME INTERNAL FUNCTIONS
*******************************************************************************/
int check_border_x(int16_t pos_x){
	if(pos_x >= MAX_X - 5)	return(right);
	if(pos_x <= 5)	return(left);
	return none;
}

int check_border_y(int16_t pos_y){
	if(pos_y >= 280)	return(down);
	if(pos_y <= 42)	return(up);
	return none;
}



/*******************************************************************************
	END INTERNAL FUNCTIONS
*******************************************************************************/

/*******************************************************************************
* Function Name  : GAME_init
* Description    : sets static variables.
* Input          : - posx: coordinates of the ball.
									 - posy: coordinates of the ball.
									 - velx: velocity of the ball.
									 - vely: velocity of the ball.
									 - color: color of the ball.
* Output         : None
* Return         : None
* Attention		 	 : None
*******************************************************************************/
void	GAME_init(void){
	BALL_init(X0,Y0,VX0,VY0);
	myscore = 0;
	pcscore = 0;
	game_status = start;
	LCD_Clear(BACKGROUND_COLOR);
	GUI_Text(5, 160, (uint8_t *)START_STRING, White, BACKGROUND_COLOR);	
}



/*******************************************************************************
* Function Name  : GAME_start
* Description    : start the game
* Input          : None
* Output         : None
* Return         : None
* Attention		 	 : None
*******************************************************************************/
void GAME_start(void){
	GUI_Text(5, 160, (uint8_t *)START_STRING, BACKGROUND_COLOR, BACKGROUND_COLOR);
	GAME_Draw();
	enable_timer(1);
	enable_timer(0);
	game_status = run;
}

/*******************************************************************************
* Function Name  : GAME_Draw_Walls
* Description    : Draw the walls on the GLCD
* Input          : None
* Output         : None
* Return         : None
* Attention		 	 : None
*******************************************************************************/
void GAME_Draw_Walls(void){
	int i;
	for(i=0;i<5;i++){
		LCD_DrawLine(i,0,i,MAX_Y,WALLS_COLOR);							//left wall
		LCD_DrawLine(MAX_X-i,0,MAX_X-i,MAX_Y,WALLS_COLOR);	//right wall
	}
}


/*******************************************************************************
* Function Name  : get_new_angle
* Description    : get new angle for the direction of the ball
									 by looking at the value of TIMER 3
* Input          : None
* Output         : None
* Return         : None
* Attention		 	 : None
*******************************************************************************/
void get_new_angle(void){
	int16_t tmp = LPC_TIM3->TC;
	if(tmp % 2){
		//if the first bit is set to one, direction of the ball is leftward
		// shift is done for not reusing the first bit
		tmp = (tmp>>1) + 1;
		BALL_set_velx(-tmp);
	}else{
		//else it is rightward	
		tmp = (tmp>>1) + 1;
		BALL_set_velx(tmp);
	}
	/****************************************************************************
	**vertical velocity is set in a way such that the sum of orizzontal velocity
	**and vertical velocity is constant
	****************************************************************************/
	tmp = tmp - 13;
	if(BALL_get_vely() < 0 ){
		tmp = -tmp;
	}
	BALL_set_vely(tmp);  
}

void ball_out(void){
	PADDLE_delete();
	AUTPADDLE_delete();
	BALL_delete();
	BALL_init(X0,Y0,VX0,VY0);
	BALL_Draw();
	AUTPADDLE_Draw(120);
	PADDLE_Draw(120);
	GAME_Draw_score(White);
}

/*******************************************************************************
* Function Name  : GAME_get_next
* Description    : compute the next status of the game (i.e. position of the ball, myscore)
* Input          : None
* Output         : None
* Return         : None
* Attention		 	 : None
*******************************************************************************/
void GAME_get_next(void){
	// COMPUTING THE NEXT POSITION OF THE BALL
	int16_t new_x = BALL_get_posx() + BALL_get_velx();
	int16_t new_y = BALL_get_posy() + BALL_get_vely();
	
	uint16_t autpaddlepos = AUTPADDLE_get_position();
	
	if(autpaddlepos > new_x ){
		AUTPADDLE_move(-3);
	}else{
		AUTPADDLE_move(3);
	}
	
	//CHECKING THE COLLISION WITH THE PADDLE
	if(PADDLE_check_collision(new_x,new_y)){
		if(BALL_get_vely() > 0){
			//*******************************************************
			//NEW ANGLE FOR THE DIRECTION OF THE BALL
			new_y = new_y - BALL_get_vely();
			get_new_angle();
			new_y = new_y + BALL_get_vely();
			new_x = new_x + BALL_get_velx();
			//*******************************************************
			
		}
		BALL_Move(new_x,new_y);
		PADDLE_Draw(PADDLE_get_position());
		return;
	}
	
	if(AUTPADDLE_check_collision(new_x,new_y)){
		if(BALL_get_vely() < 0){
			new_y = new_y - BALL_get_vely();
			get_new_angle();
			new_y = new_y + BALL_get_vely();
			new_x = new_x + BALL_get_velx();
			
		}
		BALL_Move(new_x,new_y);
		AUTPADDLE_Draw(AUTPADDLE_get_position());
		return;
	}
	
	//CHECKING THE COLLISION WITH THE LEFT BORDER
	if(check_border_x(new_x) == left && BALL_get_velx() < 0){
		
		
		BALL_set_velx(-BALL_get_velx());		//velocity has to be inverted when the ball encounters the border
		new_x = new_x + 2*BALL_get_velx();	//the position has to be recomputed
		BALL_Move(new_x,new_y);							//moving the ball in the new position
		return;
	}
	//CHECKING THE COLLISION WITH THE RIGHT BORDER
	if(check_border_x(new_x) == right && BALL_get_velx() > 0){
		
		
		BALL_set_velx(-BALL_get_velx());
		new_x = new_x + 2*BALL_get_velx();
		BALL_Move(new_x,new_y);
		return;
	}
	
	//CHECKING THE COLLISION WITH THE UPPER BORDER
	if(check_border_y(new_y) == up && BALL_get_vely() < 0){
		//PC LOSE
		myscore += 1;
		if(myscore == 5){
			inv_GUI_Text(100, 100, (uint8_t *)LOSE_STRING, White, BACKGROUND_COLOR);
			GUI_Text(10, 180, (uint8_t *)RESTART_STRING, White, BACKGROUND_COLOR);
			GUI_Text(90, 220, (uint8_t *)WIN_STRING, White, BACKGROUND_COLOR);
			disable_timer(0);
			disable_timer(1);
			game_status = stop;
		}else{
			ball_out();
		}
		return;
	}
	
	//CHECKING IF THE BALL MISS THE PADDLE
	if(check_border_y(new_y) == down && !PADDLE_check_collision(new_x,new_y)){
		//YOU LOSE
		pcscore += 1; 
				
		if(pcscore == 5){
			inv_GUI_Text(100, 100, (uint8_t *)WIN_STRING, White, BACKGROUND_COLOR);
			GUI_Text(10, 180, (uint8_t *)RESTART_STRING, White, BACKGROUND_COLOR);
			GUI_Text(90, 220, (uint8_t *)LOSE_STRING, White, BACKGROUND_COLOR);
			disable_timer(0);
			disable_timer(1);
			game_status = stop;
		}else{
			ball_out();
		}
		return;
	}
	
	//IT IS EXECUTED ONLY IF THE BALL IS INSIDE THE BORDER
	BALL_Move(new_x,new_y);
	return ;
}

/*******************************************************************************
* Function Name  : GAME_Draw_score
* Description    : Draw the score of the game.
* Input          : None
* Output         : None
* Return         : None
* Attention		 	 : None
*******************************************************************************/
void GAME_Draw_score(uint16_t color){
	char s_myscore[20];
	char s_pcscore[20];
	sprintf(s_myscore,"%d",myscore);
	sprintf(s_pcscore,"%d",pcscore);
	GUI_Text(5, 150, (uint8_t *) s_myscore, color, BACKGROUND_COLOR);
	inv_GUI_Text(230, 165, (uint8_t *) s_pcscore, color, BACKGROUND_COLOR);
}


/*******************************************************************************
* Function Name  : GAME_Draw_score
* Description    : Clear the LCD, draw the ball,the myscore and the paddle.
* Input          : None
* Output         : None
* Return         : None
* Attention		 	 : None
*******************************************************************************/
void GAME_Draw(void){
	GAME_Draw_Walls();
	PADDLE_Draw(PADDLE_get_position());
	AUTPADDLE_Draw(AUTPADDLE_get_position());
	GAME_Draw_score(White);
	BALL_Draw();
}

/*******************************************************************************
* Function Name  : GAME_pause
* Description    : Put the game in pause
* Input          : None
* Output         : None
* Return         : None
* Attention		 	 : None
*******************************************************************************/
void GAME_pause(void){
	disable_timer(0);
	disable_timer(1);
	GUI_Text(70, 175, (uint8_t *)PAUSE_STRING1, White, BACKGROUND_COLOR);
	GUI_Text(45, 195, (uint8_t *)PAUSE_STRING2, White, BACKGROUND_COLOR);
	game_status = pause;
	return;
}

/*******************************************************************************
* Function Name  : GAME_resume
* Description    : Put the game in pause
* Input          : None
* Output         : None
* Return         : None
* Attention		 	 : None
*******************************************************************************/
void GAME_resume(void){
	GUI_Text(70, 175, (uint8_t *)PAUSE_STRING1, BACKGROUND_COLOR, BACKGROUND_COLOR);
	GUI_Text(45, 195, (uint8_t *)PAUSE_STRING2, BACKGROUND_COLOR, BACKGROUND_COLOR);
	BALL_Draw();																	//redraw the ball
	enable_timer(0);
	enable_timer(1);
	game_status = run;
}

/*******************************************************************************
* Function Name  : GAME_resert
* Description    : reset the game
* Input          : None
* Output         : None
* Return         : None
* Attention		 	 : None
*******************************************************************************/
void GAME_reset(void){
	GAME_init();
	return;
}

int GAME_get_status(void){
	return game_status;
}
