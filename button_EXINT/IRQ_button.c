#include "button.h"
#include "../GAME/game.h"
#include "LPC17xx.h"
#include "../RIT/RIT.h"

extern int down0;
extern int down1;
extern int down2;


void EINT0_IRQHandler (void)	  	/* INT0														 */
{	
	down0=1;
	NVIC_DisableIRQ(EINT0_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 20);     /* GPIO pin selection */
	
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
	return;
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{	
	down1 = 1;
	NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	
	down2=1;
	NVIC_DisableIRQ(EINT2_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 24);     /* GPIO pin selection */
	
	LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */
}
