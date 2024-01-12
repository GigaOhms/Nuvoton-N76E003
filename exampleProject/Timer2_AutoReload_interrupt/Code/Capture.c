/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2017 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Nuvoton Technoledge Corp. 
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Apr/21/2017
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: N76E003 Timer2 Capture Mode demo code
//***********************************************************************************************************

#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"



uint32_t millis = 0;
uint32_t led_time;

void Timer2_ISR (void) interrupt 5
{
	clr_TF2;                                             //Clear Timer2 Interrupt Flag
	millis++;
}



void main (void)
{
    Set_All_GPIO_Quasi_Mode;
	
	TIMER2_DIV_128;
	TIMER2_Auto_Reload_Delay_Mode;
	
	RCMP2L = TIMER_DIV128_VALUE_100ms;
	RCMP2H = TIMER_DIV128_VALUE_100ms >> 8;

	TH2 = 0;
	TL2 = 0;
	
	set_TR2;
	set_ET2;
    set_EA;		// Enable global interrupts
	
	led_time = millis;

    while(1) {
		if ((uint32_t)(millis - led_time) >= 5) {
			led_time = millis;
			P12 = ~P12;
		}
	}
}


