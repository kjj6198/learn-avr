## Learn AVR programming with ATMEGA162 and ATMEGA328p

### Equipment / Software

1. EEPROM Programmer (TL866 II)
2. minipro 
3. ATMEGA328p MCU (any atmega chip is also fine), [datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2513-8-bit-AVR-Microntroller-ATmega162_Datasheet.pdf)
4. avr-gcc for compiling C, avra for compiling assembly

### How to compile / flash

Checkout src/Makefile.

* compiles `.c` file to `.hex` file
* using minipro (TL866 II) to upload your code to chip
  * `make flash` to flash your code to chip
* `make size` to check compiled file size
* `make disasm` to check generated assembly code

### Content (WIP)

- [x] GPIO: AVR microcontroller has PORTA, PORTB, PORTC IO register. (./src/gpio/gpio.c)
- [x] timer: AVR microcontroller usually have 1 ~ 3 timers (./src/timer/timer.c)
- [x] external interrupt: You can trigger external interrupt in AVR microcontroller (./src/ext_int/ext_int.c) 
- [x] usart: Rx, Tx communication (./src/usart/usart.c)
- [ ] DHT11: Using pure AVR chip to measure temperature via DHT11 (./src/dht11/dht11.c)
- [ ] flash: AVR microcontroller allows you declare const variable into flash space to save RAM (./src/flash/flash.c)
- [ ] 