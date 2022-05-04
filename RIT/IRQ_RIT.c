/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2021-01-09
** Last Version:        V1.00
** Descriptions:        functions to manage T0, T1 AND T2 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "..\GAME\game.h"

volatile int down0 = 0;
volatile int down1 = 0;
volatile int down2 = 0;

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void RIT_IRQHandler (void)
{	
	//KEY0 management
	if(down0 != 0){
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){
			reset_RIT();
			down0++;
			if(down0 == 2){
				if(GAME_get_status() == stop) GAME_reset();
			}
		}
		else{
			down0 = 0;
			NVIC_EnableIRQ(EINT0_IRQn);
			LPC_PINCON->PINSEL4 |= (1<<20);
		}
	}
	//KEY1 management
	if(down1 != 0){
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){
			reset_RIT();
			down1++;
			if(down1 == 2){
				if(GAME_get_status() == pause ) GAME_resume();
				if(GAME_get_status() == start) GAME_start();
			}
		}
		else{
			down1 = 0;
			NVIC_EnableIRQ(EINT1_IRQn);
			LPC_PINCON->PINSEL4 |= (1<<22);
		}
	}
	
	//KEY2 management
	if(down2 != 0){
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){
			reset_RIT();
			down2++;
			if(down2 == 2){
				if(GAME_get_status() == run ) GAME_pause();
			}
		}
		else{
			down2 = 0;
			NVIC_EnableIRQ(EINT2_IRQn);
			LPC_PINCON->PINSEL4 |= (1<<24);
		}
	}
	
	LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
  return;
	
}

/******************************************************************************
**                            End Of File
******************************************************************************/
