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
#include "TM1637.h"

// --------------------- Example IC 74HC595 - 8 LED - USE LIB - TM1637   ------------------------------------

#define LAT595	0
#define QH595	5
#define CLK595	10

#define ADCpin  17

#define CLK		11
#define DIO 	12

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
	uint8_t led_STT = 0x1;
	uint16_t adcValue, u16Vol;
	
	TM1637_init(&display, CLK, DIO);
	Timer0_Delay1ms(100);
	TM1637_setBrightness(&display, 0x0f); // led 7 doan
	
	pinMode(LAT595, OUTPUT);
	pinMode(QH595, OUTPUT);
	pinMode(CLK595, OUTPUT);
	pinMode(ADCpin, INPUT);
	

	while(1)
	{
		adcValue = analogRead(ADCpin);
		u16Vol = (uint16_t)(((float) adcValue * 5000.0) / 4095.0);		// convert 0-4095 --> 0-5000 mV
		
		
		
		if (adcValue >= 3584) led_STT = 0xff;
		else if (adcValue >= 3072) led_STT = 0x7f;
		else if (adcValue >= 2560) led_STT = 0x3f;
		else if (adcValue >= 2048) led_STT = 0x1f;
		else if (adcValue >= 1536) led_STT = 0xf;
		else if (adcValue >= 1024) led_STT = 0x7;
		else if (adcValue >= 512) led_STT = 0x3;
		else if (adcValue >= 0) led_STT = 0x1;
		
		out1byte(led_STT);
		showValue(u16Vol);
		
		Timer0_Delay1ms(500);
	}

}



