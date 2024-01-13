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
//  File Function: N76E003  ADC mutli channel demo code
//***********************************************************************************************************
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

#include "GPIO.h"



void main (void) 
{
	unsigned int ADCValue1, ADCValue2;
	float fVoltage1, fVoltage2;
	InitialUART0_Timer3(115200);
	TI = 1;
	
	pinMode(5, INPUT);
	pinMode(30, INPUT);

	 while (1) {
		ADCValue1 = analogRead(30);	// channel 7 - pin P30
		fVoltage1 = ((float) ADCValue1 * 5.0) / 4095.0;
		ADCValue2 = analogRead(5);	// channel 4 - pin P05
		fVoltage2 = ((float) ADCValue2 * 5.0) / 4095.0;
		 
		printf("\npin P30, P05: %.2f, %.2f", fVoltage1, fVoltage2);
		Timer0_Delay1ms(2000);

	 }
}