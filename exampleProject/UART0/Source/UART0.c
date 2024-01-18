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
//  File Function: N76E003 UART-0 Mode1 demo code
//***********************************************************************************************************
#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"


bit serial_available() {
	return RI;
}


uint8_t serial_read() {
	RI = 0;
	return SBUF;
}


void main (void) 
{
	uint8_t c;
	InitialUART0_Timer3(9600);										// 9600, 115200 - oke
	TI = 1;															// Important, use prinft function must set TI=1;
	
	while(1)
	{
		if (RI == 1) {
			RI = 0;
			c = SBUF;
			Send_Data_To_UART0(c);
		}
	}
}