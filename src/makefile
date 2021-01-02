CC = avr-gcc
MCU = atmega328p
CFLAGS += -O2 -Wall -mmcu=$(MCU)
ASM = avra
OBJDUMP = avr-objdump
OBJCOPY = avr-objcopy
AVRSIZE = avr-size
MINIPRO_DEVICE = ATMEGA328P@DIP28
LDFLAGS = -Wl,-Map

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<;

%.out: %.c
	$(CC) $(CFLAGS) $< -o $@

%.hex : %.out
	$(OBJCOPY) -O ihex $< $@

%.hex : %.s
	$(ASM) $< -o $@

%.elf : %.c
	$(CC) $(LDFLAGS),$(basename $@).map -mmcu=$(MCU) $^ -o $@

%.lst : %.elf
	$(OBJDUMP) -S $< > $@

disasm : $(file)
	cat $(file)

size : $(file)
	$(AVRSIZE) -C --mcu=$(MCU) $(file)

flash :
	minipro -w $(file) -c code -p $(MINIPRO_DEVICE)

clean :
	rm -f ./**/*.hex ./**/*.out	./**/*.elf ./**/*.lst ./**/*.map
