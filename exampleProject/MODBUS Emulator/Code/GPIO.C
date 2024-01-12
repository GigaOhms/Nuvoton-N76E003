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



// ----------------- DATA SLA --------------------------
uint8_t error1 = 0, error2 = 0, error3 = 0, error4 = 0;
uint8_t id = 0x1;
uint16_t counter = 0;
uint8_t dataSend[15];


// -------------- SERIAL MODBUS VARIABLE -------------------
#define sumSize 15U		// them 2 byte checkSum la 17
#define sizeData 14U


uint8_t serial_available() {
	return RI ? 1 : 0;
}

uint8_t serial_read() {
	uint8_t c = SBUF;
	RI = 0;
	return c;
}



void main (void) {		
	InitialUART0_Timer3(9600);	
	
	dataSend[0] = id;
	dataSend[1] = 0x3;		// value READ HOLDING REGISTERS
	dataSend[2] = 0xc;		// size of Data
	dataSend[3] = 0x0;		//highByte(error1);
	dataSend[5] = 0x0;		//highByte(error2);
	dataSend[7] = 0x0;		//highByte(error3);
	dataSend[9] = 0x0;		//highByte(error4);
	dataSend[13] = 0x0;		//highByte(id);
	
	dataSend[4] = lowByte(error1);
	dataSend[6] = lowByte(error2);
	dataSend[8] = lowByte(error3);
	dataSend[10] = lowByte(error4);
	dataSend[11] = highByte(counter);
	dataSend[12] = lowByte(counter);
	dataSend[14] = lowByte(id);
	
	sendDataModbusRTU(dataSend, sumSize);
	
	
	while(1)
	{	
	}
}



// ------------------------ END of main ------------------------------------


