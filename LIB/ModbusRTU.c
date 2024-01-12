#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

#include "ModbusRTU.h"

void sendDataModbusRTU(uint8_t dataSend[], uint8_t sizeData) { 
  uint8_t i;
  uint16_t csum;
  for (i = 0; i < sizeData; i++) {
    Send_Data_To_UART0(dataSend[i]);
    Timer0_Delay1ms(1);
  }
  csum = checkSumModbusRTU(dataSend, sizeData);
  Send_Data_To_UART0(lowByte(csum));
  Timer0_Delay1ms(1);
  Send_Data_To_UART0(highByte(csum));
  Timer0_Delay1ms(1);
}


uint16_t checkSumModbusRTU(uint8_t dataCheck[], uint8_t sizeData) {
  uint16_t crc;
  uint8_t i, j;
  crc = 0xFFFF;
  for (i = 0; i < sizeData; i++) {
    crc ^= dataCheck[i];
    for (j = 0; j < 8; j++) {
      if (crc & 1) crc = (crc >> 1) ^ 0xA001;
      else crc = (crc >> 1);
    }
  }
  return crc;
}