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

#define ADCpin 17

void main (void) 
{
	unsigned int ADCValue1;
	float fVoltage1;
	InitialUART0_Timer3(115200);
	TI = 1;
	
	pinMode(ADCpin, INPUT);

	 while (1) {
		ADCValue1 = analogRead(ADCpin);
		fVoltage1 = ((float) ADCValue1 * 5.0) / 4095.0;
		 
		//printf("\nADC value at pin 17 is: %.2f", fVoltage1);
		 
		printf("\n-1\t6\t%.2f", fVoltage1);
		Timer0_Delay1ms(100);

	 }
}