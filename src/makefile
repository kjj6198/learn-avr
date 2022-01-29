CC = avr-gcc
MCU = attiny85
CFLAGS += -O2 -Wall -mmcu=$(MCU)
ASM = avra
OBJDUMP = avr-objdump
OBJCOPY = avr-objcopy
AVRSIZE = avr-size
MINIPRO_DEVICE = ATTINY85
LDFLAGS = -Wl,-Map
SRCS=$(wildcard $(@D)/*.c)
OBJS:=$(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<;

%.out: %.c
	$(CC) $(CFLAGS) $(SRCS) -o $@

%.hex : %.out
	$(OBJCOPY) -O ihex $< $@

%.hex : %.s
	$(ASM) $< -o $@

%.elf : %.c
	$(CC) $(LDFLAGS),$(basename $@).map -mmcu=$(MCU) $(SRCS) -o $@

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
