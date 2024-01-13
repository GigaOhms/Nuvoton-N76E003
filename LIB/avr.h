#ifndef __AVR__
#define __AVR__

#define QUASI       0x0
#define OUTPUT      0x1
#define INPUT       0x2
#define INPUT_OD    0x3

#define LOW  0x0
#define HIGH 0x1

void pinMode(uint8_t pin, uint8_t mode);
bit digitalRead(uint8_t pin);
void digitalWrite(uint8_t pin, bit stt);

#endif