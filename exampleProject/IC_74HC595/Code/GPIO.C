/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2017 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Jan/21/2017
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: N76E003 GPIO demo code
//***********************************************************************************************************
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

// --------------------- Example IC 74HC595 - 8 LED ----------------------------------------------------------

void out1byte(uint8_t byteout){
	uint8_t i;
	for (i = 0; i < 8; i++){
		P05 = byteout >> 7;
		P10 = 0;
		P10 = 1;
		byteout = byteout << 1;
	}
	P00 = 0;
	P00 = 1;
}

void ON_LED(uint8_t * STT, uint8_t n){
	if (n < 1 || n > 8) return ;
	*STT |= (1 << (n - 1));
	out1byte(*STT);
}

void OFF_LED(uint8_t * STT, uint8_t n){
	if (n < 1 || n > 8) return ;
	*STT &= ~(1 << (n - 1));
	out1byte(*STT);
}

void main (void) 
{
//	Set_All_GPIO_Quasi_Mode;					// Define in Function_define.h
	uint8_t led_STT = 0, i = 0;
	
	P00_PushPull_Mode;		// LAT595
	P05_PushPull_Mode;		// QH595
	P10_PushPull_Mode;		// CLK595
	
	// PUSH_PULL la OUTPUT low-high
	

	while(1)
	{
		for (i = 1; i <= 8; i++) {
			ON_LED(&led_STT, i);
			Timer0_Delay1ms(500);
		}
		Timer0_Delay1ms(500);
		for (i = 1; i <= 8; i++) {
			OFF_LED(&led_STT, i);
			Timer0_Delay1ms(500);
		}
		Timer0_Delay1ms(500);
	}

}



