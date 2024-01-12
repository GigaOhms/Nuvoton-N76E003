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
#include "I2Ceeprom.h"


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
uint16_t counter = 0;


// -------------- SERIAL MODBUS VARIABLE -------------------
#define sumSize 15U		// them 2 byte checkSum la 17
#define sizeData 14U

uint8_t xdata dataSend[15];	// 3 byte resigter and u16data[]

bit checkID = 0;
bit checkSend = 0;
bit checkWrite = 0;
bit checkSerial = 0;

uint8_t xdata reciveCounter = 0;
uint8_t xdata reciveData[8];
uint32_t xdata serialTime = 0;

#define serialTimeout 30UL

uint8_t serial_available() {
	return RI ? 1 : 0;
}

uint8_t serial_read() {
	uint8_t c = SBUF;
	RI = 0;
	return c;
}


// -------------- GPIO SETUP -----------------------
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



void showError(uint8_t error, uint8_t value) {
  uint8_t datas[] = { 0, 0, 0, 0 };
  datas[0] = TM1637_encodeDigit(14);
  datas[1] = TM1637_encodeDigit(error);
  datas[2] = 0x00;			// 0x40 is '-' 			// 0x00 is ' '
  datas[3] = TM1637_encodeDigit(value);
  TM1637_setSegments(&display, datas);
  Timer0_Delay1ms(500);
}

void dataUpdate() {
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



// I2C 
#define addrE1	0
#define addrE2	1
#define addrE3	2
#define addrE4	3
#define addrCNT 4
#define addrID	6



void main (void) {		
	InitialUART0_Timer3(9600);	
	I2C_Init();
	
	/*
	if (I2C_Write(addrE1, 1));
	Timer0_Delay1ms(1);
	if (I2C_Write(addrE2, 1));
	Timer0_Delay1ms(1);
	if (I2C_Write(addrE3, 1));
	Timer0_Delay1ms(1);
	if (I2C_Write(addrE4, 1));
	Timer0_Delay1ms(1);
	if (I2C_Write(addrID, 1));
	Timer0_Delay1ms(1);
	if (I2C_WriteInt(addrCNT, 99));
	Timer0_Delay1ms(1);
	*/
	
	
	
	if (I2C_Read(addrE1, &error1));
	if (I2C_Read(addrE2, &error2));
	if (I2C_Read(addrE3, &error3));
	if (I2C_Read(addrE4, &error4));
	if (I2C_Read(addrID, &id));
	if (I2C_ReadInt(addrCNT, &counter));

	Send_Data_To_UART0(id);
	
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
	
	dataSend[0] = lowByte(id);
	dataSend[1] = 0x3;		// value READ HOLDING REGISTERS
	dataSend[2] = 0xc;		// size of Data
	dataSend[3] = 0x0;		//highByte(error1);
	dataSend[5] = 0x0;		//highByte(error2);
	dataSend[7] = 0x0;		//highByte(error3);
	dataSend[9] = 0x0;		//highByte(error4);
	dataSend[13] = 0x0;		//highByte(id);

	dataUpdate();
	led_time = millis;
	serialTime = millis;
	
	while(1)
	{	
		if (digitalRead(BT_UP) == 0 && S_BT_UP == 0) {
			S_BT_UP = 1;
			counter = (counter >= 9999) ? counter : counter + 1;
			dataUpdate();
			showValue(counter);
			Timer0_Delay1ms(200);
			if (I2C_WriteInt(addrCNT, counter))
				Timer0_Delay1ms(1);
		} else if (digitalRead(BT_UP) == 1) S_BT_UP = 0;
		
		if (digitalRead(BT_DW) == 0 && S_BT_DW == 0) {
			S_BT_DW = 1;
			counter = (counter == 0) ? counter : counter - 1;
			dataUpdate();
			showValue(counter);
			Timer0_Delay1ms(200);
			if (I2C_WriteInt(addrCNT, counter))
				Timer0_Delay1ms(1);
		} else if (digitalRead(BT_DW) == 1) S_BT_DW = 0;
		
		if (digitalRead(BT_E1) == 0 && S_BT_E1 == 0) {
			S_BT_E1 = 1;
			error1 = (error1 == 1) ? 0 : 1;
			dataUpdate();
			showError(1, error1);
			if (I2C_Write(addrE1, error1))
				Timer0_Delay1ms(1);
			Timer0_Delay1ms(200);
			showValue(counter);
		} else if (digitalRead(BT_E1) == 1) S_BT_E1 = 0;

		if (digitalRead(BT_E2) == 0 && S_BT_E2 == 0) {
			S_BT_E2 = 1;
			error2 = (error2 == 1) ? 0 : 1;
			dataUpdate();
			showError(2, error2);
			if (I2C_Write(addrE2, error2))
				Timer0_Delay1ms(1);
			Timer0_Delay1ms(200);
			showValue(counter);
		} else if (digitalRead(BT_E2) == 1) S_BT_E2 = 0;
		
		if (digitalRead(BT_E3) == 0 && S_BT_E3 == 0) {
			S_BT_E3 = 1;
			error3 = (error3 == 1) ? 0 : 1;
			dataUpdate();
			showError(3, error3);
			if (I2C_Write(addrE3, error3))
				Timer0_Delay1ms(1);
			Timer0_Delay1ms(200);
			showValue(counter);
		} else if (digitalRead(BT_E3) == 1) S_BT_E3 = 0;
		
		if (digitalRead(BT_E4) == 0 && S_BT_E4 == 0) {
			S_BT_E4 = 1;
			error4 = (error4 == 1) ? 0 : 1;
			dataUpdate();
			showError(4, error4);
			Timer0_Delay1ms(200);
			showValue(counter);
			if (I2C_Write(addrE4, error4))
				Timer0_Delay1ms(1);
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
						//dataUpdate();
						sendDataModbusRTU(dataSend, sumSize);
					} else if (reciveData[1] == 0x6) {		// 0x6 - Single Holding Register
						if (reciveData[3] == 0) {
							error1 = reciveData[5];
							showError(1, error1);
							if (I2C_Write(addrE1, error1))
								Timer0_Delay1ms(1);
						} else if (reciveData[3] == 1) {
							error2 = reciveData[5];
							showError(2, error2);
							if (I2C_Write(addrE2, error2))
								Timer0_Delay1ms(1);
						} else if (reciveData[3] == 2) {
							error3 = reciveData[5];
							showError(3, error3);
							if (I2C_Write(addrE3, error3))
								Timer0_Delay1ms(1);
						} else if (reciveData[3] == 3) {
							error4 = reciveData[5];
							showError(4, error4);
							if (I2C_Write(addrE4, error4))
								Timer0_Delay1ms(1);
						} else if (reciveData[3] == 4) {
							counter = (reciveData[4] << 8) ^ reciveData[5];
						} else if (reciveData[3] == 5) {
							id = reciveData[5];
							dataSend[0] = lowByte(id);
							if (I2C_Write(addrID, id))
								Timer0_Delay1ms(1);
						}
						dataUpdate();
						showValue(counter);
						if (I2C_WriteInt(addrCNT, counter))
							Timer0_Delay1ms(1);
					}
				}
			}
		}
	}
}



// ------------------------ END of main ------------------------------------


