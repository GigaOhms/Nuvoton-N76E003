#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#include "avr.h"

#include "TM1637.h"

#define TM1637_I2C_COMM1    0x40
#define TM1637_I2C_COMM2    0xC0
#define TM1637_I2C_COMM3    0x80


const uint8_t xdata digitToSegment[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 }; // 0 -> F

static const uint8_t minusSegments = 0x40;

void TM1637_init(TM1637* display, uint8_t pinClk, uint8_t pinDIO) {
  display->pinClk = pinClk;
  display->pinDIO = pinDIO;

  pinMode(display->pinClk, INPUT_OD);
  pinMode(display->pinDIO, INPUT_OD);

  digitalWrite(display->pinClk, LOW);
  digitalWrite(display->pinDIO, LOW);
}

void TM1637_setBrightness(TM1637* display, uint8_t brightness) {
  display->brightness = (brightness & 0x7) | 0x08;
}

void TM1637_setSegments(TM1637* display, const uint8_t segments[]) {
  uint8_t xdata k;
	
  TM1637_start(display->pinDIO);
  TM1637_writeByte(display, TM1637_I2C_COMM1);
  TM1637_stop(display->pinDIO, display->pinClk);

  TM1637_start(display->pinDIO);
  TM1637_writeByte(display, TM1637_I2C_COMM2 + (0 & 0x03));

  for (k = 0; k < 4; k++) 
    TM1637_writeByte(display, segments[k]);
	
  TM1637_stop(display->pinDIO, display->pinClk);

  TM1637_start(display->pinDIO);
  TM1637_writeByte(display, TM1637_I2C_COMM3 + (display->brightness & 0x0f));
  TM1637_stop(display->pinDIO, display->pinClk);
}


void TM1637_clear(TM1637* display) {
  uint8_t xdata datas[4] = {0, 0, 0, 0};
  TM1637_setSegments(display, datas);
}


void TM1637_start(uint8_t pinDIO) {
  digitalWrite(pinDIO, LOW);
  Timer0_Delay100us(1);
}

void TM1637_stop(uint8_t pinDIO, uint8_t pinClk) {
  digitalWrite(pinDIO, LOW);
  Timer0_Delay100us(1);
  digitalWrite(pinClk, HIGH);
  Timer0_Delay100us(1);
  digitalWrite(pinDIO, HIGH);
  Timer0_Delay100us(1);
}

uint8_t TM1637_writeByte(TM1637* display, uint8_t b) {
  uint8_t xdata dataa = b;
  uint8_t xdata i, ack;
	
  for (i = 0; i < 8; i++) {
    digitalWrite(display->pinClk, LOW);
    Timer0_Delay100us(1);
    if (dataa & 0x01)
      digitalWrite(display->pinDIO, HIGH);
    else
      digitalWrite(display->pinDIO, LOW);
    Timer0_Delay100us(1);
    digitalWrite(display->pinClk, HIGH);
    Timer0_Delay100us(1);
    dataa = dataa >> 1;
  }

  digitalWrite(display->pinClk, LOW);
  digitalWrite(display->pinDIO, HIGH);
  Timer0_Delay100us(1);

  digitalWrite(display->pinClk, HIGH);
  Timer0_Delay100us(1);

  ack = (uint8_t)digitalRead(display->pinDIO);
  if (ack == 0)
    digitalWrite(display->pinDIO, LOW);

  Timer0_Delay100us(1);
  digitalWrite(display->pinClk, LOW);
  Timer0_Delay100us(1);
  
  return ack;
}

uint8_t TM1637_encodeDigit(uint8_t digit) {
  return digitToSegment[digit & 0x0f];
}