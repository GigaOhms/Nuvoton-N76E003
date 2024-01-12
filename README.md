# Nuvoton-N76E003

Project using Nuvoton-N76E003 8051 and library TM1637 Display, I2C EEPROM AT24Cx 24LCx , pinMode like arduino, Modbus send data emulator....

#### Download [package KeilC or IAR for N76E003](https://www.nuvoton.com/products/microcontrollers/8bit-8051-mcus/low-pin-count-8051-series/n76e003/?group=Software&tab=2) or this Repo
#### Use [USB VNpro in KeilC](https://www.nuvoton.com/products/microcontrollers/8bit-8051-mcus/low-pin-count-8051-series/n76e003/?group=Software&tab=2) or [USB VNpro in  ISP Prog v6](http://vidieukhien.org/phan-mem-isp-prog-v6.html) to upload program

## `__ Some default command __ (một số lệnh mặc định)`
### GPIO
    P04_PushPull_Mode;                  // Set gpio P04 chế độ Push-pull
    P11_Quasi_Mode ;                    // Set gpio P11 chế độ Quasi
### UART
    InitialUART0_Timer3(9600);          // khởi tạo uart 0 cho timer3 với tốc độ baud là 9600 (có thể đặt
    4800,115200....)
    InitialUART1_Timer3(baudRate);      // Khởi tạo uart 1 cho timer3
    TI = 1;                             // Sử dụng khi muốn dùng hàm `printf()`
    Send_Data_To_UART0(byteData);       // Gửi 1 byte qua uart
    printf("Hello world");              // Sử dụng như hàm printf
    
### Timer delay
    Timer0_Delay100us(UINT32 u32CNT);
    Timer0_Delay1ms(UINT32 u32CNT);
    Timer1_Delay10ms(UINT32 u32CNT);
    Timer2_Delay500us(UINT32 u32CNT);
    Timer3_Delay100ms(UINT32 u32CNT);
    
    Timer0_Delay40ms(UINT32 u32CNT);
    Timer3_Delay10us(UINT32 u32CNT);

### Timer2 interrupt 
    void Timer2_ISR (void) interrupt 5                      // Timer2 ISR funtion
    {
    	clr_TF2;                                            // Clear Timer2 Interrupt Flag
    }
    
	// --------------- Setup ISR timer2 1kHz -----------------------
	TIMER2_DIV_4;
	TIMER2_Auto_Reload_Delay_Mode;
	RCMP2L = TIMER_DIV4_VALUE_1ms;
	RCMP2H = TIMER_DIV4_VALUE_1ms >> 8;
	TH2 = 0;
	TL2 = 0;
	set_TR2;
	set_ET2;
    set_EA;		// Enable global interrupts

&nbsp;
&nbsp;

## `__ USE Library __ (sử dụng library)`
Download folder `LIB`, save to package folder.

Open project in keilC, go to `Options for Target` -> `tab C51`, add `..\..\LIB` to `Include Paths`

&nbsp;

### `_ GPIO Setup _ (sử dụng thư viện avr.h tự tạo)`
USE library `avr.h` __ Sử dụng thư viện avr.h

    #include "avr.h"

- Config gpio `P12`, `P04` output mode:
```c
pinMode(12, OUTPUT);
pinMode(4, OUTPUT);
```

| Mode | Description |
| ------  | ----------- |
| QUASI   | Config gpio quasi mode __ (đặt gpio làm đầu vào và ra, xuất mức logic cao-thấp, nhận tín hiệu input) |
| OUTPUT  | Config gpio push-pull mode __ (xuất mức logic cao-thấp)|
| INPUT   | Config gpio input only mode __ (chỉ làm đầu vào) |
| INPUT_OD| Config gpio input Open-drain mode __ (xuất mức logic thấp và nhận tín hiệu đầu vào) |

&nbsp;

### `_ digital-Write-Read _`

- Set output gpio `P15` to `HIGH`, gpio `P05` to `LOW`
```c
digitalWrite(15, HIGH);
digitalWrite(5, LOW);
```

- Reads the value from digital pin `P11`, `P03`

```c
digitalRead(11);
digitalRead(3);
```
&nbsp;

### `Tạo 2 hàm nhận dữ liệu Serial cơ bản như arduino`
```c
uint8_t serial_available() {
	return RI ? 1 : 0;
}

uint8_t serial_read() {
	uint8_t c = SBUF;
	RI = 0;
	return c;
}
```
