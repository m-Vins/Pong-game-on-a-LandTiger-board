/*********************************************************************************************************
** Author:		             	Vincenzo Mezzela
** Creation date:           17/12/2021
** Notes:										All the function starting with prefix "AUT" is referred to the automatic paddle
*********************************************************************************************************/

#include "game.h"
#include "paddle.h"
#include "../GLCD/GLCD.h"

#define 	CENTER 	120
#define 	LENGTH 	50
#define 	WIDTH 	10
#define 	HEIGHT 	278

#define AUT_HEIGHT 32

uint16_t old_pos = 120;
uint16_t aut_old_pos = 120;




/*******************************************************************************
* Function Name  : PADDLE_Draw
* Description    : Draw the paddle.
* Input          : - pos: specifies the paddle old_pos.
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void PADDLE_Draw(uint16_t pos){
	uint8_t i;
	
	if(pos<25){
		pos=25;
	}
	
	if(pos>240-25){
		pos=240-25;
	}
	for(i = 0; i<WIDTH; i++){
		LCD_DrawLine(pos-LENGTH/2,HEIGHT+i,pos+LENGTH/2,HEIGHT+i,PADDLE_COLOR);
	}
	old_pos = pos;
}

/*******************************************************************************
* Function Name  : AUTPADDLE_Draw
* Description    : Draw the automatic paddle.
* Input          : - pos: specifies the paddle old_pos.
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void AUTPADDLE_Draw(uint16_t pos){
	uint8_t i;
	
	if(pos<25){
		pos=25;
	}
	
	if(pos>240-25){
		pos=240-25;
	}
	for(i = 0; i<WIDTH; i++){
		LCD_DrawLine(pos-LENGTH/2,AUT_HEIGHT+i,pos+LENGTH/2,AUT_HEIGHT+i,PADDLE_COLOR);
	}
	aut_old_pos = pos;
}

/*******************************************************************************
* Function Name  : PADDLE_get_position
* Description    : get the paddle position.
* Input          : None
* Output         : None
* Return         : the position of the paddle.
* Attention		 	 : None
*******************************************************************************/
uint16_t PADDLE_get_position(void){
	return old_pos;
}

/*******************************************************************************
* Function Name  : AUTPADDLE_get_position
* Description    : get the paddle position.
* Input          : None
* Output         : None
* Return         : the position of the paddle.
* Attention		 	 : None
*******************************************************************************/
uint16_t AUTPADDLE_get_position(void){
	return aut_old_pos;
}

/*******************************************************************************
* Function Name  : PADDLE_check_collision
* Description    : check if a collision occours.
* Input          : - pos_x_ball: specifies x coordinate.
									 - pos_y_ball: specifies x coordinate.
* Output         : None
* Return         : 1 if a collision occours
* Attention		 : None
*******************************************************************************/
uint8_t PADDLE_check_collision(uint16_t pos_x_ball,uint16_t pos_y_ball){

	if(pos_y_ball >= HEIGHT && pos_x_ball>= old_pos-LENGTH/2 && pos_x_ball<= old_pos+LENGTH/2){
		return 1;
	}
	return 0;
}

/*******************************************************************************
* Function Name  : AUTPADDLE_check_collision
* Description    : check if a collision occours with automatic paddle.
* Input          : - pos_x_ball: specifies x coordinate.
									 - pos_y_ball: specifies x coordinate.
* Output         : None
* Return         : 1 if a collision occours
* Attention		 : None
*******************************************************************************/
uint8_t AUTPADDLE_check_collision(uint16_t pos_x_ball,uint16_t pos_y_ball){

	if(pos_y_ball <= AUT_HEIGHT + WIDTH && pos_x_ball>= aut_old_pos-LENGTH/2 && pos_x_ball<= aut_old_pos+LENGTH/2){
		return 1;
	}
	return 0;
}



/*******************************************************************************
* Function Name  : PADDLE_move
* Description    : move the paddle towards wither right or left.
* Input          : - directions : direction of the movement.
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void PADDLE_move(uint16_t new_pos){
		int i,movement;
			
	
		if(new_pos >= 240 - 25 - 5){	new_pos = 240-25-5;}
		if(new_pos < 25+5 )			 {	new_pos = 25+5;	}
				
		movement = new_pos - old_pos;
		
		if(movement < 3 && movement > -3) return; 
		if(movement > 30 && movement < -30) return; //to make the paddle more stable 
		
		if(movement > LENGTH || movement < -LENGTH){
			for(i = 0; i< WIDTH; i++){
				LCD_DrawLine(old_pos-LENGTH/2,HEIGHT+i,old_pos+LENGTH/2,HEIGHT+i,BACKGROUND_COLOR); 	//deleting old part
				LCD_DrawLine(new_pos-LENGTH/2,HEIGHT+i,new_pos+LENGTH/2,HEIGHT+i,PADDLE_COLOR); 	//drawing new part
			}	
			old_pos = new_pos;
			return;
		}
		if(movement > 0 ){
			//PADDLE IS MOVING RIGHT
			for(i = 0; i< WIDTH; i++){
				LCD_DrawLine(old_pos-LENGTH/2,HEIGHT+i,old_pos-LENGTH/2+movement,HEIGHT+i,BACKGROUND_COLOR); 	//deleting old part
				LCD_DrawLine(old_pos+LENGTH/2,HEIGHT+i,old_pos+LENGTH/2+movement,HEIGHT+i,PADDLE_COLOR); 		//drawing new part
			}
		}
		if(movement < 0){
			//PADDLE IS MOVING LEFT
			for(i = 0; i< WIDTH; i++){
				LCD_DrawLine(old_pos+LENGTH/2+movement,HEIGHT+i,old_pos+LENGTH/2,HEIGHT+i,BACKGROUND_COLOR); 	//deleting old part
				LCD_DrawLine(old_pos-LENGTH/2+movement,HEIGHT+i,old_pos-LENGTH/2,HEIGHT+i,PADDLE_COLOR); 		//drawing new part
			}
		}
		
		old_pos = new_pos;
		return;
}

/*******************************************************************************
* Function Name  : AUTPADDLE_move
* Description    : move the automatic paddle towards either right or left.
* Input          : - directions : direction of the movement.
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void AUTPADDLE_move(int16_t movement){
		int i;
		uint16_t new_pos = aut_old_pos + movement;
	
		if(new_pos >= 240 - 25-5){	new_pos = 240-25-5;}
		if(new_pos < 25 +5)			 {	new_pos = 25+5;	}
				
		movement = new_pos - aut_old_pos; //in order to avoid overpassing the border
		
		
		if(movement > LENGTH || movement < -LENGTH){
			for(i = 0; i< WIDTH; i++){
				LCD_DrawLine(aut_old_pos-LENGTH/2,AUT_HEIGHT+i,aut_old_pos+LENGTH/2,AUT_HEIGHT+i,BACKGROUND_COLOR); 	//deleting old part
				LCD_DrawLine(new_pos-LENGTH/2,AUT_HEIGHT+i,new_pos+LENGTH/2,AUT_HEIGHT+i,PADDLE_COLOR); 	//drawing new part
			}	
			aut_old_pos = new_pos;
			return;
		}
		if(movement > 0 ){
			//PADDLE IS MOVING RIGHT
			for(i = 0; i< WIDTH; i++){
				LCD_DrawLine(aut_old_pos-LENGTH/2,AUT_HEIGHT+i,aut_old_pos-LENGTH/2+movement,AUT_HEIGHT+i,BACKGROUND_COLOR); 	//deleting old part
				LCD_DrawLine(aut_old_pos+LENGTH/2,AUT_HEIGHT+i,aut_old_pos+LENGTH/2+movement,AUT_HEIGHT+i,PADDLE_COLOR); 		//drawing new part
			}
		}
		if(movement < 0){
			//PADDLE IS MOVING LEFT
			for(i = 0; i< WIDTH; i++){
				LCD_DrawLine(aut_old_pos+LENGTH/2+movement,AUT_HEIGHT+i,aut_old_pos+LENGTH/2,AUT_HEIGHT+i,BACKGROUND_COLOR); 	//deleting old part
				LCD_DrawLine(aut_old_pos-LENGTH/2+movement,AUT_HEIGHT+i,aut_old_pos-LENGTH/2,AUT_HEIGHT+i,PADDLE_COLOR); 		//drawing new part
			}
		}
		
		aut_old_pos = new_pos;
		return;
}

void PADDLE_delete(void){
	int i ;
	
	for(i = 0; i<WIDTH; i++){
		LCD_DrawLine(old_pos-LENGTH/2,HEIGHT+i,old_pos+LENGTH/2,HEIGHT+i,BACKGROUND_COLOR);
	}
}

void AUTPADDLE_delete(void){
	int i ;
	
	for(i = 0; i<WIDTH; i++){
		LCD_DrawLine(aut_old_pos-LENGTH/2,AUT_HEIGHT+i,aut_old_pos+LENGTH/2,AUT_HEIGHT+i,BACKGROUND_COLOR);
	}
}

