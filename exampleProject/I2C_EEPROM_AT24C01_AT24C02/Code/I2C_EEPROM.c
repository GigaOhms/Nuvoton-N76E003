#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

#include "I2Ceeprom.h"


// ------------------------ MAIN -----------------------

#define WAIT_I2C 2

void main(void)
{
    char a = 0x0;
    char b = 0x0;
    char c = 0x0;
    char d = 0x0;

	uint16_t sum, sum1;

	P1M1 &= ~(1 << 2);
    P1M2 |= (1 << 2);
	P12 = 0;
    InitialUART0_Timer3(115200);
    TI = 1;	
	
	/* init */
	I2C_Init();
	
	/* check address */
	if (!I2C_CheckAddress(EEPROM_SLA)) {
		while (1) {
			P12 = 1;
			Timer0_Delay1ms(500);
			P12 = 0;
			Timer0_Delay1ms(500);
            printf("Check Error\n");
		}
	}
	
	Timer0_Delay1ms(WAIT_I2C);
	
	/* write data */
	
	if (!I2C_WriteInt(2, 1234)) {
		while (1) {
			P12 = 1;
			Timer0_Delay1ms(500);
			P12 = 0;
			Timer0_Delay1ms(500);
            printf("Write data Error 1\n");
		}
	}
	/*
	if (!I2C_Write(6, 0x04)) {
		while (1) {
			P12 = 1;
			Timer0_Delay1ms(500);
			P12 = 0;
			Timer0_Delay1ms(500);
            printf("Write data Error 1\n");
		}
	}
	
	
	Timer0_Delay1ms(WAIT_I2C);

	if (!I2C_Write(7, 0xD2)) {
		while (1) {
			P12 = 1;
			Timer0_Delay1ms(500);
			P12 = 0;
			Timer0_Delay1ms(500);
            printf("Write data Error 1\n");
		}
	}
	*/
	
	
	Timer0_Delay1ms(WAIT_I2C);

	if (!I2C_WriteInt(4, 5678)) {
		while (1) {
			P12 = 1;
			Timer0_Delay1ms(500);
			P12 = 0;
			Timer0_Delay1ms(500);
            printf("Write data Error 2\n");
		}
	}
	Timer0_Delay1ms(WAIT_I2C);

	if (!I2C_Read(6, &a)) {
		while (1) {
			Timer0_Delay1ms(1000);
            printf("Read data Error 3\n");
		}
	}
	if (!I2C_Read(7, &b)) {
		while (1) {
			Timer0_Delay1ms(1000);
            printf("Read data Error 4\n");
		}
	}
	
	if (!I2C_ReadInt(4, &sum1)) {
		while (1) {
			Timer0_Delay1ms(1000);
            printf("Read data Error 5\n");
		}
	}
	if (!I2C_ReadInt(6, &sum)) {
		while (1) {
			Timer0_Delay1ms(1000);
            printf("Read data Error 5\n");
		}
	}

	//sum = (a << 8) | b;
	
	Timer0_Delay1ms(500);
    printf("Code test PASS\n");
	

	while (1) {
		P12 = 1;
		Timer0_Delay1ms(500);
		P12 = 0;
		Timer0_Delay1ms(500);
        printf("Data read: %d %d 0x%2x 0x%2x \n", sum, sum1, a & 0xff, b & 0xff);
	}
}


