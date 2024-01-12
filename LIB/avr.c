
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"

#include "avr.h"

void pinMode(uint8_t pin, uint8_t mode) {
    bit registerPin = 0;
	if (pin == 8 || pin == 9 || pin >= 18 || mode > 0x3)
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


/*
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"

#include "avr.h"

void pinMode(uint8_t pin, uint8_t mode) {
	if (pin == 0) {
        if (mode == INPUT) {
            P00_OpenDrain_Mode;
        } else if (mode == OUTPUT)
            P00_PushPull_Mode;
	} else if (pin == 1) {
        if (mode == INPUT) {
            P01_OpenDrain_Mode;
        } else if (mode == OUTPUT)
            P01_PushPull_Mode;
	} else if (pin == 2) {
        if (mode == INPUT) {
            P02_OpenDrain_Mode;
        } else if (mode == OUTPUT)
            P02_PushPull_Mode;
	} else if (pin == 3) {
        if (mode == INPUT) {
            P03_OpenDrain_Mode;
        } else if (mode == OUTPUT)
            P03_PushPull_Mode;
	} else if (pin == 4) {
        if (mode == INPUT) {
            P04_OpenDrain_Mode;
        } else if (mode == OUTPUT)
            P04_PushPull_Mode;
	} else if (pin == 5) {
        if (mode == INPUT) {
            P05_OpenDrain_Mode;
        } else if (mode == OUTPUT)
            P05_PushPull_Mode;
	} else if (pin == 6) {
        if (mode == INPUT) {
            P06_OpenDrain_Mode;
        } else if (mode == OUTPUT)
            P06_PushPull_Mode;
	} else if (pin == 7) {
        if (mode == INPUT) {
            P07_OpenDrain_Mode;
        } else if (mode == OUTPUT)
            P07_PushPull_Mode;
	} else if (pin == 10) {
        if (mode == INPUT) {
            P10_OpenDrain_Mode;
        } else if (mode == OUTPUT)
            P10_PushPull_Mode;
	} else if (pin ==11) {
        if (mode == INPUT) {
            P11_OpenDrain_Mode;
        } else if (mode == OUTPUT)
            P11_PushPull_Mode;
	} else if (pin == 12) {
        if (mode == INPUT) {
            P12_OpenDrain_Mode;
        } else if (mode == OUTPUT)
            P12_PushPull_Mode;
	} else if (pin == 13) {
        if (mode == INPUT) {
            P13_OpenDrain_Mode;
        } else if (mode == OUTPUT)
            P13_PushPull_Mode;
	} else if (pin == 14) {
        if (mode == INPUT) {
            P14_OpenDrain_Mode;
        } else if (mode == OUTPUT)
            P14_PushPull_Mode;
	} else if (pin == 15) {
        if (mode == INPUT) {
            P15_OpenDrain_Mode;
        } else if (mode == OUTPUT)
            P15_PushPull_Mode;
	} else if (pin == 16) {
        if (mode == INPUT) {
            P16_OpenDrain_Mode;
        } else if (mode == OUTPUT)
            P16_PushPull_Mode;
	} else if (pin == 17) {
        if (mode == INPUT) {
            P17_OpenDrain_Mode;
        } else if (mode == OUTPUT)
            P17_PushPull_Mode;
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
    }
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
*/
