#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

#include "I2Ceeprom2.h"


// ------------------------ MAIN -----------------------

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
	if (!I2C_CheckAddress(0xA0)) {
		while (1) {
			P12 = 1;
			Timer0_Delay1ms(500);
			P12 = 0;
			Timer0_Delay1ms(500);
            printf("Check Error\n");
		}
	}
	
	Timer0_Delay1ms(1);
	
	/* write data */
	if (!I2C_WriteInt(2, 1570)) {
		while (1) {
			P12 = 1;
			Timer0_Delay1ms(500);
			P12 = 0;
			Timer0_Delay1ms(500);
            printf("Write data Error\n");
		}
	}
	
	Timer0_Delay1ms(1);

	if (!I2C_WriteInt(4, 2023)) {
		while (1) {
			P12 = 1;
			Timer0_Delay1ms(500);
			P12 = 0;
			Timer0_Delay1ms(500);
            printf("Write data Error\n");
		}
	}
	Timer0_Delay1ms(1);

	if (!I2C_Read(2, &a)) {
		while (1) {
			Timer0_Delay1ms(1000);
            printf("Read data Error\n");
		}
	}
	if (!I2C_Read(3, &b)) {
		while (1) {
			Timer0_Delay1ms(1000);
            printf("Read data Error\n");
		}
	}
	if (!I2C_ReadInt(4, &sum1)) {
		while (1) {
			Timer0_Delay1ms(1000);
            printf("Read data Error\n");
		}
	}


	sum = (a << 8) | b;
	
	Timer0_Delay1ms(500);
    printf("Code test PASS\n");
	

	while (1) {
		P12 = 1;
		Timer0_Delay1ms(500);
		P12 = 0;
		Timer0_Delay1ms(500);
        printf("Data read: %d %d\n", sum, sum1);
	}
}


