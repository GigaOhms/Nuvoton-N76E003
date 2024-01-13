
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"

#include "GPIO.h"

void pinMode(uint8_t pin, uint8_t mode) {
    bit registerPin = 0;

    if (pin == 8 || pin == 9 || mode > 0x3)
        return;

    if (pin == 30) {
        if (mode == QUASI) {
            P3M1 &= ~(1 << 0);
            P3M2 &= ~(1 << 0);
        } else if (mode == OUTPUT) {
            P3M1 &= ~(1 << 0);
            P3M2 |= (1 << 0);
        } else if (mode == INPUT) {
            P3M1 |= (1 << 0);
            P3M2 &= ~(1 << 0);
        } else if (mode == INPUT_OD) {
            P3M1 |= (1 << 0);
            P3M2 |= (1 << 0);
        }
    }

	if (pin >= 18)
        return;
    
    registerPin = (pin >= 10) ? 1 : 0;	// P1.x or P0.x
    pin %= 10;
    
        
    if (mode == QUASI) {
        if (registerPin == 1) {
            P1M1 &= ~(1 << pin);
            P1M2 &= ~(1 << pin);
        } else {
            P0M1 &= ~(1 << pin);
            P0M2 &= ~(1 << pin);
        }
    } else if (mode == OUTPUT) {
        if (registerPin == 1) {
            P1M1 &= ~(1 << pin);
            P1M2 |= (1 << pin);
        } else {
            P0M1 &= ~(1 << pin);
            P0M2 |= (1 << pin);
        }
    } else if (mode == INPUT) {
        if (registerPin == 1) {
            P1M1 |= (1 << pin);
            P1M2 &= ~(1 << pin);
        } else {
            P0M1 |= (1 << pin);
            P0M2 &= ~(1 << pin);
        }
    } else if (mode == INPUT_OD) {
        if (registerPin == 1) {
            P1M1 |= (1 << pin);
            P1M2 |= (1 << pin);
        } else {
            P0M1 |= (1 << pin);
            P0M2 |= (1 << pin);
        }
    }
}


bit digitalRead(uint8_t pin) {
    if (pin == 0) {
        return P00;
    } else if (pin == 1) {
        return P01;
    } else if (pin == 2) {
        return P02;
    } else if (pin == 3) {
        return P03;
    } else if (pin == 4) {
        return P04;
    } else if (pin == 5) {
        return P05;
    } else if (pin == 6) {
        return P06;
    } else if (pin == 7) {
        return P07;
    } else if (pin == 10) {
        return P10;
    } else if (pin == 11) {
        return P11;
    } else if (pin == 12) {
        return P12;
    } else if (pin == 13) {
        return P13;
    } else if (pin == 14) {
        return P14;
    } else if (pin == 15) {
        return P15;
    } else if (pin == 16) {
        return P16;
    } else if (pin == 17) {
        return P17;
    } else return 0;
}

void digitalWrite(uint8_t pin, bit stt) {
    if (pin == 0) {
        P00 = stt;
    } else if (pin == 1) {
        P01 = stt;
    } else if (pin == 2) {
        P02 = stt;
    } else if (pin == 3) {
        P03 = stt;
    } else if (pin == 4) {
        P04 = stt;
    } else if (pin == 5) {
        P05 = stt;
    } else if (pin == 6) {
        P06 = stt;
    } else if (pin == 7) {
        P07 = stt;
    } else if (pin == 10) {
        P10 = stt;
    } else if (pin == 11) {
        P11 = stt;
    } else if (pin == 12) {
        P12 = stt;
    } else if (pin == 13) {
        P13 = stt;
    } else if (pin == 14) {
        P14 = stt;
    } else if (pin == 15) {
        P15 = stt;
    } else if (pin == 16) {
        P16 = stt;
    } else if (pin == 17) {
        P17 = stt;
    }
}

uint16_t ADC_Read(uint8_t u8Channel)
{
	uint16_t value = 0x0000;
	
	ADCCON1 |= (1 << 0);

	// clock
	ADCCON1 &= ~(0x30);
	ADCCON1 |= 0x00;
	
	// set channel
	ADCCON0 &= ~(0x0F);
	ADCCON0 |= (u8Channel & 0x07);
	AINDIDS = 0x00;
	AINDIDS |= (1 << u8Channel);
	
	// clear flag
	ADCF = 0;
	//start convert
	ADCS = 1;
	
	while(ADCF == 0);
	value = (ADCRH << 4) | ADCRL;
	
	// disable ADC
	ADCCON1 &= ~(1 << 0);

	
	return value;
}


uint16_t analogRead(uint8_t pin) {
    if (pin == 17) {
        return ADC_Read(0);
    } else if (pin == 30) {
        return ADC_Read(1);
    } else if (pin == 7) {
        return ADC_Read(2);
    } else if (pin == 6) {
        return ADC_Read(3);
    } else if (pin == 5) {
        return ADC_Read(4);
    } else if (pin == 4) {
        return ADC_Read(5);
    } else if (pin == 3) {
        return ADC_Read(6);
    } else if (pin == 11) {
        return ADC_Read(7);
    }
    return 0;
}