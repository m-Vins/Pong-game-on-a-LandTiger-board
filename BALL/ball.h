/*********************************************************************************************************
** Author:		             	Vincenzo Mezzela
** Creation date:           17/12/2021		
*********************************************************************************************************/

#include "LPC17xx.h"

#define BALL_COLOR Green


/* Private function prototypes -----------------------------------------------*/
void	BALL_init(int16_t posx,int16_t posy,int16_t velx,int16_t vely);
void BALL_Draw(void);
void BALL_Move(int16_t x, int16_t y);
int16_t BALL_get_posx(void);
int16_t BALL_get_posy(void);
int16_t BALL_get_velx(void);
int16_t BALL_get_vely(void);
void BALL_set_velx(int16_t velx);
void BALL_set_vely(int16_t vely);
void BALL_set_posx(int16_t posx);
void BALL_set_posx(int16_t posx);
void BALL_delete(void);


