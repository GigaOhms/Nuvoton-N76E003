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

#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

#include "avr.h"
#include "TM1637.h"


/*------------------------------------------------
The main C function.  Program execution starts
here after stack initialization.
------------------------------------------------*/

#define CLK 11
#define DIO 12

TM1637 display;

void showValue(int so)
{
  int xdata d = so / 1000;
  int xdata c = ((so / 100) % 10);
  int xdata b = (so % 100) / 10;
  int xdata a = so % 10;

  uint8_t datas[] = { 0xff, 0xff, 0xff, 0xff };
  datas[0] = TM1637_encodeDigit(d);
  datas[1] = TM1637_encodeDigit(c);
  datas[2] = TM1637_encodeDigit(b);
  datas[3] = TM1637_encodeDigit(a);
  TM1637_setSegments(&display, datas);
}


// ----------------- DATA SLA --------------------------
uint8_t error1 = 0, error2 = 0, error3 = 0, error4 = 0;
uint8_t id = 0x1;
uint16_t counter = 1025;




void main (void) {		
	TM1637_init(&display, CLK, DIO);
	Timer0_Delay1ms(100);
	TM1637_setBrightness(&display, 0x0f); // led 7 doan
	showValue(counter);
	
	while(1)
	{}
}



// ------------------------ END of main ------------------------------------


