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

#include "GPIO.h"

// --------------------- Example IC 74HC595 - 8 LED - USE LIB  ----------------------------------------------------------

#define LAT595	0
#define QH595	5
#define CLK595	10

void out1byte(uint8_t byteout){
	uint8_t i;
	for (i = 0; i < 8; i++){
		digitalWrite(QH595, (byteout >> 7) & 0x1);
		digitalWrite(CLK595, LOW);
		digitalWrite(CLK595, HIGH);
		byteout = byteout << 1;
	}
	digitalWrite(LAT595, LOW);
	digitalWrite(LAT595, HIGH);
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
	uint8_t led_STT = 0, i = 0;
	
	pinMode(LAT595, OUTPUT);
	pinMode(QH595, OUTPUT);
	pinMode(CLK595, OUTPUT);
	
	

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



