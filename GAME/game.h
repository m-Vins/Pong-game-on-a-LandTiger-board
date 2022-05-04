/*********************************************************************************************************
** Author:		             	Vincenzo Mezzela
** Creation date:           17/12/2021
*********************************************************************************************************/

#include "LPC17xx.h"
#define BACKGROUND_COLOR Black
#define WALLS_COLOR Red


enum game_status_t{start,run,pause,stop};


/* Private function prototypes -----------------------------------------------*/
void GAME_init(void);
void GAME_start(void);
void GAME_reset(void);
void GAME_get_next(void);
void GAME_Draw(void);
void GAME_Draw_Walls(void);
void GAME_Draw_score(uint16_t color);
void GAME_pause(void);
void GAME_resume(void);
int  GAME_get_status(void);
