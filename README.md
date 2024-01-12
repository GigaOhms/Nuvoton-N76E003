# Nuvoton-N76E003

Project using Nuvoton-N76E003 8051 and library TM1637 Display, I2C EEPROM AT24Cx 24LCx , pinMode like arduino, Modbus send data emulator....


### `__ GPIO Setup __`
USE library `avr.h`

    #include "avr.h"

- Config gpio `P12`, `P04` output mode:
```c
pinMode(12, OUTPUT);
pinMode(4, OUTPUT);
```

| Mode | Description |
| ------  | ----------- |
| QUASI   | Config gpio quasi mode (input, output low-high) |
| OUTPUT  | Config gpio push-pull mode |
| INPUT   | Config gpio input only mode |
| INPUT_OD| Config gpio input Open-drain mode |


### `__ digital-Write-Read __`

- Set output gpio `P15` to `HIGH`, gpio `P05` to `LOW`
```c
digitalWrite(15, HIGH);
digitalWrite(5, HIGH);
```

- Reads the value from digital pin `P11`, `P03`

```c
digitalRead(11);
digitalRead(3);
```
