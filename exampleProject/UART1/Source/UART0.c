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


bit serial1_available() {
	return RI_1;
}


uint8_t serial1_read() {
	RI_1 = 0;
	return SBUF_1;
}


void main (void) 
{
	InitialUART1_Timer3(9600);										// 9600, 115200 - oke
	
	while(1)
	{
		if (serial1_available() == 1) {
			uint8_t c = serial1_read();
			Send_Data_To_UART1(c);
		}
	}
}