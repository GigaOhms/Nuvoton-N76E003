# Nuvoton-N76E003

Project using Nuvoton-N76E003 8051 and library TM1637 Display, I2C EEPROM AT24Cx 24LCx , pinMode like arduino, Modbus send data emulator....

#### Datasheet [N76E003AT20](https://www.nuvoton.com/export/resource-files/DS_N76E003_EN_Rev1.10.pdf)

#### Download [package KeilC or IAR for N76E003](https://www.nuvoton.com/products/microcontrollers/8bit-8051-mcus/low-pin-count-8051-series/n76e003/?group=Software&tab=2) or this Repo
#### Use [USB VNpro in KeilC](http://vidieukhien.org/tich-hop-kit-vdk-1-0-vao-keil-c.html) or [USB VNpro in  ISP Prog v6](http://vidieukhien.org/phan-mem-isp-prog-v6.html) to upload program

## Tutorial and example project:
- [VN](http://vidieukhien.org/category/8051/ms51fb9ae)
- [EN](https://embedded-lab.com/blog/getting-started-nuvoton-8-bit-microcontrollers-coding-part-1/)

&nbsp;

## `__ Some default command __ (một số lệnh mặc định)`
### GPIO
```c
P04_PushPull_Mode;                  // Set gpio P04 chế độ Push-pull    - Output low-high
P11_Quasi_Mode;                     // Set gpio P11 chế độ Quasi        - Output low-high, input
P05_Input_Mode;                     // Set gpio P05 chế độ Input        - Input
P12_OpenDrain_Mode;                 // Set gpio P12 chế độ Open-Drain   - Output low, input

P04 = 1                             // Set gpio P04 lên cao (mức 1)
P11 = 0                             // Set gpio P04 mức thấp (mức 0)
value = P05;                        // Đọc giá trị input ở gpio P05 (low - high)

```

### UART
```c
InitialUART0_Timer3(9600);          // khởi tạo uart 0 cho timer3 với tốc độ baud là 9600
InitialUART1_Timer3(baudRate);      // Khởi tạo uart 1 cho timer3
Send_Data_To_UART0(byteData);       // Gửi 1 byte qua uart
TI = 1;                             // Sử dụng khi muốn dùng hàm `printf()`
printf("Hello world");              // Sử dụng như hàm printf trong C, gửi dữ liệu qua Serial
```
    
### Timer delay __ Các hàm delay được tạo sẵn

```c
Timer0_Delay100us(u32CNT);
Timer0_Delay1ms(u32CNT);
Timer1_Delay10ms(u32CNT);
Timer2_Delay500us(u32CNT);
Timer3_Delay100ms(u32CNT);
Timer0_Delay40ms(u32CNT);
Timer3_Delay10us(u32CNT);
```


&nbsp;

## `__ USE Library __ (sử dụng thư viện tự tạo)`
Download folder `LIB`, save to package folder.

Open project in keilC, go to `Options for Target` -> `tab C51`, add `..\..\LIB` to `Include Paths`

&nbsp;

### `_ GPIO Setup _ (sử dụng thư viện "GPIO.h" tự tạo)`
USE library `GPIO.h` __ Sử dụng thư viện GPIO.h
```c
    #include "GPIO.h"
```

- Config gpio `P12` output, `P04` input, `P05` Open drain mode:
```c
pinMode(12, OUTPUT);
pinMode(4,  INPUT);
pinMode(4,  INPUT_OD);
```

| Mode    | Description |
| ------  | ----------- |
| QUASI   | Config gpio quasi mode __ (đặt gpio làm đầu vào và ra, xuất mức logic cao-thấp, nhận tín hiệu input)|
| OUTPUT  | Config gpio push-pull mode __ (xuất mức logic cao-thấp)|
| INPUT   | Config gpio input only mode __ (chỉ làm đầu vào) |
| INPUT_OD| Config gpio input Open-drain mode __ (xuất mức logic mức thấp và nhận tín hiệu đầu vào) |

&nbsp;

### `_ digital-Write-Read _ đọc, ghi tín hiệu digital`

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

### `_ analogRead _ đọc tín hiệu ADC gpio`

- N76E003 có 8 gpio có thể đọc tín hiệu ADC là các chân gpio `AINx` (x = 0 -> 7)

- Đọc giá trị analog từ gpio P11
```c
pinMode(11, INPUT);

while(1) {
    adaValue = analogRead(11);
}
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
&nbsp;

### `Timer2 interrupt __ tạo ngắt Timer2 1kHz (dùng như millis() trên arduino)`
```c
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
set_TR2;    // Timer2 run
set_ET2;    // Enable Timer2 interrupt
set_EA;		// Enable global interrupts
```
