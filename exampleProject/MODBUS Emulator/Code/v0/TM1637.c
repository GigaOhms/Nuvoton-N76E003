// #include <stdlib.h>
// #include <string.h>
// #include <inttypes.h>

#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#include "avr.h"

#include "TM1637.h"

#define TM1637_I2C_COMM1    0x40
#define TM1637_I2C_COMM2    0xC0
#define TM1637_I2C_COMM3    0x80

/*
const uint8_t digitToSegment[] = {
 // XGFEDCBA
  0b00111111,    // 0
  0b00000110,    // 1
  0b01011011,    // 2
  0b01001111,    // 3
  0b01100110,    // 4
  0b01101101,    // 5
  0b01111101,    // 6
  0b00000111,    // 7
  0b01111111,    // 8
  0b01101111,    // 9
  0b01110111,    // A
  0b01111100,    // b
  0b00111001,    // C
  0b01011110,    // d
  0b01111001,    // E
  0b01110001,    // F
  0b00000000     //
  };
  */
  
const uint8_t digitToSegment[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x00 };

static const uint8_t minusSegments = 0x40;

void TM1637_init(TM1637* display, uint8_t pinClk, uint8_t pinDIO) {
  display->pinClk = pinClk;
  display->pinDIO = pinDIO;

  pinMode(display->pinClk, INPUT);
  pinMode(display->pinDIO, INPUT);

  //digitalWrite(display->pinClk, LOW);
  //digitalWrite(display->pinDIO, LOW);
}

void TM1637_setBrightness(TM1637* display, uint8_t brightness) {
  display->brightness = (brightness & 0x7) | 0x08;
}

void TM1637_setSegments(TM1637* display, const uint8_t segments[]) {
  TM1637_start(display->pinDIO);
  TM1637_writeByte(display, TM1637_I2C_COMM1);
  TM1637_stop(display->pinDIO, display->pinClk);

  TM1637_start(display->pinDIO);
  TM1637_writeByte(display, TM1637_I2C_COMM2 + (0 & 0x03));
/*
  unsigned char k;
  for (k = 0; k < 4; k++) {
    TM1637_writeByte(display, segments[k]);
  }
	*/
	
  TM1637_writeByte(display, segments[0]);
  TM1637_writeByte(display, segments[1]);
  TM1637_writeByte(display, segments[2]);
  TM1637_writeByte(display, segments[3]);
	
  TM1637_stop(display->pinDIO, display->pinClk);

  TM1637_start(display->pinDIO);
  TM1637_writeByte(display, TM1637_I2C_COMM3 + (display->brightness & 0x0f));
  TM1637_stop(display->pinDIO, display->pinClk);
}


void TM1637_clear(TM1637* display) {
  uint8_t datas[4] = {0, 0, 0, 0};
  TM1637_setSegments(display, datas);
}



void TM1637_start(uint8_t pinDIO) {
  pinMode(pinDIO, OUTPUT);
  Timer0_Delay100us(1);
}

void TM1637_stop(uint8_t pinDIO, uint8_t pinClk) {
  pinMode(pinDIO, OUTPUT);
  Timer0_Delay100us(1);
  pinMode(pinClk, INPUT);
  Timer0_Delay100us(1);
  pinMode(pinDIO, INPUT);
  Timer0_Delay100us(1);
}

void TM1637_writeByte(TM1637* display, uint8_t b) {
  uint8_t dataa = b;
  uint8_t i;
  for (i = 0; i < 8; i++) {

    pinMode(display->pinClk, OUTPUT);
    Timer0_Delay100us(1);

    if (dataa & 0x01)
      pinMode(display->pinDIO, INPUT);
    else
      pinMode(display->pinDIO, OUTPUT);
    Timer0_Delay100us(1);

    pinMode(display->pinClk, INPUT);
    Timer0_Delay100us(1);
    dataa = dataa >> 1;
  }

  pinMode(display->pinClk, OUTPUT);
  pinMode(display->pinDIO, INPUT);
  Timer0_Delay100us(1);

  pinMode(display->pinClk, INPUT);
  Timer0_Delay100us(1);
  //bit ack;
  //ack = digitalRead(display->pinDIO);
  if (digitalRead(display->pinDIO) == 0)
    pinMode(display->pinDIO, OUTPUT);

  Timer0_Delay100us(1);
  pinMode(display->pinClk, OUTPUT);
  Timer0_Delay100us(1);
}

uint8_t TM1637_encodeDigit(uint8_t digit) {
  return digitToSegment[digit & 0x0f];
}