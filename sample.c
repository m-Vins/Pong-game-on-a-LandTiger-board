/*********************************************************************************************************
** Author:		             	Vincenzo Mezzela
** Creation date:           17/12/2021
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TIMER/timer.h"
#include "button_EXINT/button.h"
#include "game.h"
#include "ADC/adc.h"
#include "RIT/rit.h"

#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif



int main(void)
{
  SystemInit();  												//System Initialization 
	LCD_Initialization();
	BUTTON_init();												//BUTTON initialization
	
	
	//ADC management
	init_timer(1,0xc8);										//50ms * 25MHz ~= 0x1312D0
	ADC_init();
	
	//GLCD management & GAME management
	init_timer(0, 0xC8 ); 						    //8us * 25MHz ~= 0xC8 
	GAME_init();
	
	
	//RIT for button debouncing
	init_RIT(0x004C4B40);									/* RIT Initialization 50 msec       	*/
	enable_RIT();													/* enable RIT to count 50ms				 */
	
	//FOR RANDOM ANGLE FUNCTION
	init_timer(3,0x12);
	enable_timer(3);
	
	LPC_SC->PCON |= 0x1;									//power-down	mode										
	LPC_SC->PCON &= ~(0x2);						

	
  while (1)	
  {
		__ASM("wfi");
  }
}
