	/*********************************************************************************************************
** Author:		             	Vincenzo Mezzela
** Creation date:           17/12/2021
** Notes:										All the function starting with prefix "AUT" is referred to the automatic paddle
*********************************************************************************************************/

#include "LPC17xx.h"

#define PADDLE_COLOR Green

/* Private function prototypes -----------------------------------------------*/
void PADDLE_Draw(uint16_t pos);
uint16_t PADDLE_get_position(void);
uint8_t PADDLE_check_collision(uint16_t pos_x_ball,uint16_t pos_y_ball);
void PADDLE_move(uint16_t pos);
void PADDLE_delete(void);
	
void AUTPADDLE_Draw(uint16_t pos);
void AUTPADDLE_move(int16_t movement);
uint8_t AUTPADDLE_check_collision(uint16_t pos_x_ball,uint16_t pos_y_ball);
uint16_t AUTPADDLE_get_position(void);
void AUTPADDLE_delete(void);
