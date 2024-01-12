#ifndef __MUDBUSRTU__
#define __MUDBUSRTU__

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

uint16_t checkSumModbusRTU(uint8_t dataCheck[], uint8_t sizeData);
void sendDataModbusRTU(uint8_t dataSend[], uint8_t sizeData);

#endif
