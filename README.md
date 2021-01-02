## Learn AVR programming with ATMEGA162 and ATMEGA328p

### Equipment / Software

1. EEPROM Programmer (TL866 II)
2. minipro 
3. ATMEGA162 MCU (any atmega chip is also fine), [datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2513-8-bit-AVR-Microntroller-ATmega162_Datasheet.pdf)
4. avr-gcc for compiling C, avra for compiling assembly

### How to compile / flash

1. `avra ./main.s` compile assembly into .hex file
2. use TL866 II for flashing.
   `minipro -w ./main.hex -c code -p ATMEGA162`
3. `avr-gcc -O2 -Wall -mmcu=atmega162 ./main.c -o ./main.out`

