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

// --------------------- Example IC 74HC165 - 8 BUTTON ------------------------------------------------------


#define SHLD165 P04
#define CLK165  P01
#define INH165  P03
#define QH165   P02


uint8_t in1byte() {
	uint8_t i, incoming = 0, dataa = 0, dataas = 0;
	SHLD165 = 0;
	SHLD165 = 1;
	INH165  = 0;
	for (i = 0; i < 8; i++) {
		incoming = incoming << 1;
		if (QH165 == 0)
			incoming = incoming | 0x1;
		CLK165 = 1;
		CLK165 = 0;
	}
	dataas = ~incoming;
	return dataas;
}

#define BT_DW 0x7f
#define BT_UP 0xf7
#define BT_E1 0xbf
#define BT_E2 0xfb
#define BT_E3 0xfe
#define BT_E4 0xfd

#define WAIT_BTN 200

bit S_BT_DW = 0;
bit S_BT_UP = 0;
bit S_BT_E1 = 0;
bit S_BT_E2 = 0;
bit S_BT_E3 = 0;
bit S_BT_E4 = 0;

void main (void) 
{
//	Set_All_GPIO_Quasi_Mode;					// Define in Function_define.h
	uint8_t BTN = 0, i = 0;
	
	InitialUART0_Timer3(9600);
	TI = 1;
	
	P01_PushPull_Mode;		// CLK165
	P04_PushPull_Mode;		// SHLD165
	P03_PushPull_Mode;		// INH165
	P02_Input_Mode;			// QH165
	
	P00_PushPull_Mode;		// LAT165
	P05_PushPull_Mode;		// QH595
	P10_PushPull_Mode;		// CLK595
	
	// PUSH_PULL la OUTPUT low-high
	

	while(1)
	{
		BTN = in1byte();
		//out1byte(BTN);		// Test with 74HC595
		
		if (BTN == BT_DW && S_BT_DW == 0) {
			S_BT_DW = 1;
			printf("\nBT_DW");
			Timer0_Delay1ms(WAIT_BTN);
		} else if (BTN == 0xff) S_BT_DW = 0;
		
		if (BTN == BT_UP && S_BT_UP == 0) {
			S_BT_UP = 1;
			printf("\nBT_UP");
			Timer0_Delay1ms(WAIT_BTN);
		} else if (BTN == 0xff) S_BT_UP = 0;
		
		if (BTN == BT_E1 && S_BT_E1 == 0) {
			S_BT_E1 = 1;
			printf("\nBT_E1");
			Timer0_Delay1ms(WAIT_BTN);
		} else if (BTN == 0xff) S_BT_E1 = 0;
		
		if (BTN == BT_E2 && S_BT_E2 == 0) {
			S_BT_E2 = 1;
			printf("\nBT_E2");
			Timer0_Delay1ms(WAIT_BTN);
		} else if (BTN == 0xff) S_BT_E2 = 0;
		
		if (BTN == BT_E3 && S_BT_E3 == 0) {
			S_BT_E3 = 1;
			printf("\nBT_E3");
			Timer0_Delay1ms(WAIT_BTN);
		} else if (BTN == 0xff) S_BT_E3 = 0;
		
		if (BTN == BT_E4 && S_BT_E4 == 0) {
			S_BT_E4 = 1;
			printf("\nBT_E4");
			Timer0_Delay1ms(WAIT_BTN);
		} else if (BTN == 0xff) S_BT_E4 = 0;
			
	}

}



