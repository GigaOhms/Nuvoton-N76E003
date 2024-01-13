// USE pinMode, digitalRead, digitalWrite like Arduino
// Ex: P12 -> pinMode(12, OUTPUT);
// Ex: P04 -> pinMode(4, OUTPUT);

#ifndef __GPIO__
#define __GPIO__

#define QUASI       0x0
#define OUTPUT      0x1
#define INPUT       0x2
#define INPUT_OD    0x3

#define LOW  0x0
#define HIGH 0x1

void pinMode(uint8_t pin, uint8_t mode);
bit digitalRead(uint8_t pin);
void digitalWrite(uint8_t pin, bit stt);
uint16_t ADC_Read(uint8_t u8Channel);
uint16_t analogRead(uint8_t pin);
#endif