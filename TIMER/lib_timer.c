#include "lpc17xx.h"
#include "timer.h"

/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0,1 or 2
** Returned value:		None
**
******************************************************************************/
void enable_timer( uint8_t timer_num )
{
	switch(timer_num){
		case(0):
			LPC_TIM0->TCR = 1;
			break;
		case(1):
			LPC_TIM1->TCR = 1;
			break;
		case(2):
			LPC_TIM2->TCR = 1;
			break;
		case(3):
			LPC_TIM3->TCR = 1;
			break;
		default:
			break;
	}
	return;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0,1 or 2
** Returned value:		None
**
******************************************************************************/
void disable_timer( uint8_t timer_num )
{
		switch(timer_num){
		case(0):
			LPC_TIM0->TCR = 0;
			break;
		case(1):
			LPC_TIM1->TCR = 0;
			break;
		case(2):
			LPC_TIM2->TCR = 0;
			break;
		case(3):
			LPC_TIM3->TCR = 0;
			break;
		default:
			break;
	}
  return;
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0,1 or 2
** Returned value:		None
**
******************************************************************************/
void reset_timer( uint8_t timer_num )
{
  uint32_t regVal;
	
		switch(timer_num){
		case(0):
			regVal = LPC_TIM0->TCR;
			regVal |= 0x02;
			LPC_TIM0->TCR = regVal;
			break;
		case(1):
			regVal = LPC_TIM1->TCR;
			regVal |= 0x02;
			LPC_TIM1->TCR = regVal;
			break;
		case(2):
			regVal = LPC_TIM2->TCR;
			regVal |= 0x02;
			LPC_TIM2->TCR = regVal;
			break;
		case(3):
			regVal = LPC_TIM3->TCR;
			regVal |= 0x02;
			LPC_TIM3->TCR = regVal;
			break;
		default:
			break;
	}

}

uint32_t init_timer ( uint8_t timer_num, uint32_t TimerInterval )
{
	
		switch(timer_num){
		case(0):
			LPC_TIM0->MR0 = TimerInterval;
			LPC_TIM0->MCR = 3;
			NVIC_EnableIRQ(TIMER0_IRQn);
			return (1);
		case(1):
			LPC_TIM1->MR0 = TimerInterval;
			LPC_TIM1->MCR = 3;				
			NVIC_EnableIRQ(TIMER1_IRQn);
			return (1);
		case(2):
			LPC_TIM2->MR0 = TimerInterval;
			LPC_TIM2->MCR = 3;				
			NVIC_EnableIRQ(TIMER2_IRQn);
			return (1);
		case(3):
			LPC_TIM3->MR0 = TimerInterval;
			LPC_TIM3->MCR = 2;				/* HERE IS DIFFERENT BECAUSE NO INTERRUPT IS NEEDED */
			return(1);
		default:
			break;
	}
  return (0);
}

/******************************************************************************
**                            End Of File
******************************************************************************/
