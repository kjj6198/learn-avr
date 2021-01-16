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
- [x] external interrupt: you can trigger external interrupt in AVR microcontroller (./src/ext_int/ext_int.c)
- [ ] pin change interrupt: you can trigger pin change interrupt (PCINT) in AVR microcontroller
- [x] usart: Rx, Tx communication (./src/usart/usart.c)
- [ ] watchdog: be able to detect if program has hang up or not
- [ ] DHT11: Using pure AVR chip to measure temperature via DHT11 (./src/dht11/dht11.c)
- [x] flash: AVR microcontroller allows you declare const variable into flash space to save RAM (./src/flash/flash.c)
- [ ] SPI: (wip)
- [ ] I2C: (wip)
- [ ] EEPROM: (wip)


### TODOs

* extract USART functionality

### Resources

* [RJH Coding AVR Toturial](http://www.rjhcoding.com/index.php)
* [程式人雜誌 - ATMEGA328p](http://programmermagazine.github.io/201406/htm/article1.html)
* [AVR YouTube playlist](https://www.youtube.com/playlist?list=PLC9kTpqIk-EJXR9XwJy_S0Tepm1Agef4-)
* [Make: AVR Programming (book)](https://learning.oreilly.com/library/view/make-avr-programming/9781449356484/)
  * [Example code](https://github.com/hexagon5un/AVR-Programming)
