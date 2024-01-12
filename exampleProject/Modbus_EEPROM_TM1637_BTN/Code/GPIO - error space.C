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

#include "avr.h"
#include "TM1637.h"
#include "ModbusRTU.h"
//#include "I2Ceeprom.h"

//*****************  The Following is in define in Fucntion_define.h  ***************************
//****** Always include Function_define.h call the define you want, detail see main(void) *******
//***********************************************************************************************
#if 0
#endif

/*------------------------------------------------
The main C function.  Program execution starts
here after stack initialization.
------------------------------------------------*/

#define CLK 11
#define DIO 12

TM1637 display;

void showValue(int so)
{
  int d = so / 1000;
  int c = ((so / 100) % 10);
  int b = (so % 100) / 10;
  int a = so % 10;

  uint8_t datas[] = { 0xff, 0xff, 0xff, 0xff };
  datas[0] = TM1637_encodeDigit(d);
  datas[1] = TM1637_encodeDigit(c);
  datas[2] = TM1637_encodeDigit(b);
  datas[3] = TM1637_encodeDigit(a);
  TM1637_setSegments(&display, datas);
}



#define sumSize 15U		// them 2 byte checkSum la 17
#define sizeData 14U


uint8_t dataSend[15];	// 3 byte resigter and u16data[]


bit checkID = 0;
bit checkSend = 0;
bit checkWrite = 0;
bit checkSerial = 0;

uint8_t reciveCounter = 0;
uint8_t reciveData[8];
uint32_t serialTime = 0;

#define serialTimeout 30UL

#define BT_UP 4
#define BT_DW 10
#define BT_E1 0
#define BT_E2 3
#define BT_E3 1
#define BT_E4 2

bit S_BT_UP = 0;
bit S_BT_DW = 0;
bit S_BT_E1 = 0;
bit S_BT_E2 = 0;
bit S_BT_E3 = 0;
bit S_BT_E4 = 0;



uint8_t serial_available() {
	return RI ? 1 : 0;
}

uint8_t serial_read() {
	uint8_t c = SBUF;
	RI = 0;
	return c;
}

void showError(uint8_t error, uint8_t value) {
  uint8_t datas[] = { 0, 0, 0, 0 };
  datas[0] = TM1637_encodeDigit(14);
  datas[1] = TM1637_encodeDigit(error);
  datas[2] = 0x00;			// 0x40 is '-' 			// 0x00 is ' '
  datas[3] = TM1637_encodeDigit(value);
  TM1637_setSegments(&display, datas);
  Timer0_Delay1ms(500);
}

void dataUpdate(uint8_t error1, uint8_t error2, uint8_t error3, uint8_t error4, uint16_t counter, uint8_t id) {
	dataSend[4] = lowByte(error1);
	dataSend[6] = lowByte(error2);
	dataSend[8] = lowByte(error3);
	dataSend[10] = lowByte(error4);
	dataSend[11] = highByte(counter);
	dataSend[12] = lowByte(counter);
	dataSend[14] = lowByte(id);
}


volatile uint32_t xdata millis = 0;
volatile uint32_t xdata led_time;

void Timer2_ISR (void) interrupt 5
{
	clr_TF2;                                             //Clear Timer2 Interrupt Flag
	millis++;
}


	// ---------------- DATA  SLAVE --------------------------
	uint8_t error1, error2, error3, error4, id;
	uint16_t counter = 0;

void main (void) {		

	
	InitialUART0_Timer3(9600);		
	//I2C_Init();
	
	
	
	// --------------- ISR timer2 1kHz -----------------------
	TIMER2_DIV_4;
	TIMER2_Auto_Reload_Delay_Mode;
	RCMP2L = TIMER_DIV4_VALUE_1ms;
	RCMP2H = TIMER_DIV4_VALUE_1ms >> 8;
	TH2 = 0;
	TL2 = 0;
	set_TR2;
	set_ET2;
    set_EA;		// Enable global interrupts
	
	// ------------------- GPIO Config ------------------------
	pinMode(BT_UP, INPUT);
	pinMode(BT_DW, INPUT);
	pinMode(BT_E1, INPUT);
	pinMode(BT_E2, INPUT);
	pinMode(BT_E3, INPUT);
	pinMode(BT_E4, INPUT);
	
	TM1637_init(&display, CLK, DIO);
	Timer0_Delay1ms(100);
	
	TM1637_setBrightness(&display, 0x0f); // led 7 doan
	showValue(counter);
	
	dataSend[0] = id;		// ID slave
	dataSend[1] = 0x3;		// value READ HOLDING REGISTERS
	dataSend[2] = 0xc;		// size of Data
	dataSend[3] = 0x0;		//highByte(error1);
	dataSend[5] = 0x0;		//highByte(error2);
	dataSend[7] = 0x0;		//highByte(error3);
	dataSend[9] = 0x0;		//highByte(error4);
	dataSend[13] = 0x0;		//highByte(id);

	dataUpdate(error1, error2, error3, error4, counter, id);
	led_time = millis;
	serialTime = millis;

	while(1)
	{	
		
		if (digitalRead(BT_UP) == 0 && S_BT_UP == 0) {
			S_BT_UP = 1;
			counter = (counter >= 9999) ? counter : counter + 1;
			dataUpdate(error1, error2, error3, error4, counter, id);
			showValue(counter);
			Timer0_Delay1ms(200);
		} else if (digitalRead(BT_UP) == 1) S_BT_UP = 0;
		
		if (digitalRead(BT_DW) == 0 && S_BT_DW == 0) {
			S_BT_DW = 1;
			counter = (counter == 0) ? counter : counter - 1;
			dataUpdate(error1, error2, error3, error4, counter, id);
			showValue(counter);
			Timer0_Delay1ms(200);
		} else if (digitalRead(BT_DW) == 1) S_BT_DW = 0;
		
		if (digitalRead(BT_E1) == 0 && S_BT_E1 == 0) {
			S_BT_E1 = 1;
			error1 = (error1 == 1) ? 0 : 1;
			dataUpdate(error1, error2, error3, error4, counter, id);
			showError(1, error1);
			Timer0_Delay1ms(200);
			showValue(counter);
		} else if (digitalRead(BT_E1) == 1) S_BT_E1 = 0;

		if (digitalRead(BT_E2) == 0 && S_BT_E2 == 0) {
			S_BT_E2 = 1;
			error2 = (error2 == 1) ? 0 : 1;
			dataUpdate(error1, error2, error3, error4, counter, id);
			showError(2, error2);
			Timer0_Delay1ms(200);
			showValue(counter);
		} else if (digitalRead(BT_E2) == 1) S_BT_E2 = 0;
		
		if (digitalRead(BT_E3) == 0 && S_BT_E3 == 0) {
			S_BT_E3 = 1;
			error3 = (error3 == 1) ? 0 : 1;
			dataUpdate(error1, error2, error3, error4, counter, id);
			showError(3, error3);
			Timer0_Delay1ms(200);
			showValue(counter);
		} else if (digitalRead(BT_E3) == 1) S_BT_E3 = 0;
		
		if (digitalRead(BT_E4) == 0 && S_BT_E4 == 0) {
			S_BT_E4 = 1;
			error4 = (error4 == 1) ? 0 : 1;
			dataUpdate(error1, error2, error3, error4, counter, id);
			showError(4, error4);
			Timer0_Delay1ms(200);
			showValue(counter);
		} else if (digitalRead(BT_E4) == 1) S_BT_E4 = 0;
		
		
		if ((uint32_t)(millis - led_time) >= 2000) {
			led_time = millis;
			//sendDataModbusRTU(dataSend, sumSize);
			P12 = ~P12;
		}
		
		if (serial_available()) {
			uint8_t c = serial_read();
			if ((uint32_t)(millis - serialTime) > serialTimeout) {
				serialTime = millis;
				reciveCounter = 0;
			}
			reciveData[reciveCounter] = c;
			reciveCounter++;
			if (reciveCounter >= 8) {
				reciveCounter = 0;
				if (reciveData[0] == id) {
					if (reciveData[1] == 0x3) {				// 0x3 - READ HOLDING REGISTERS 
						sendDataModbusRTU(dataSend, sumSize);
					} else if (reciveData[1] == 0x6) {		// 0x6 - Single Holding Register
						if (reciveData[3] == 0) {
							error1 = reciveData[5];
							showError(1, error1);
						} else if (reciveData[3] == 1) {
							error2 = reciveData[5];
							showError(2, error2);
						} else if (reciveData[3] == 2) {
							error3 = reciveData[5];
							showError(3, error3);
						} else if (reciveData[3] == 3) {
							error4 = reciveData[5];
							showError(4, error4);
						} else if (reciveData[3] == 4) {
							counter = (reciveData[4] << 8) ^ reciveData[5];
						} else if (reciveData[3] == 5) {
							id = reciveData[5];
						}
						dataUpdate(error1, error2, error3, error4, counter, id);
						showValue(counter);
					}
				}
			}
		}
	}
}



// ------------------------ END of main ------------------------------------


