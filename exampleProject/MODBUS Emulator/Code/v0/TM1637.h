#ifndef __TM1637__
#define __TM1637__


#define SEG_A   0b00000001
#define SEG_B   0b00000010
#define SEG_C   0b00000100
#define SEG_D   0b00001000
#define SEG_E   0b00010000
#define SEG_F   0b00100000
#define SEG_G   0b01000000
#define SEG_DP  0b10000000
#define DEFAULT_BIT_DELAY  100

typedef struct {
    uint8_t pinClk;
    uint8_t pinDIO;
    uint8_t brightness;
} TM1637;

void TM1637_init(TM1637* display, uint8_t pinClk, uint8_t pinDIO);
void TM1637_setBrightness(TM1637* display, uint8_t brightness);
void TM1637_setSegments(TM1637* display, const uint8_t segments[]);
void TM1637_clear(TM1637* display);
void TM1637_start(uint8_t pinDIO);
void TM1637_writeByte(TM1637* display, uint8_t b);
void TM1637_stop(uint8_t pinDIO, uint8_t pinClk);
uint8_t TM1637_encodeDigit(uint8_t digit);

#endif
