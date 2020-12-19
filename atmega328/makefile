CC = avr-gcc
CFLAGS += -O2 -Wall -mmcu=atmega328p
ASM = avra
OBJCOPY = avr-objcopy
MINIPRO_DEVICE = ATMEGA328P@DIP28

%.out: %.c
	$(CC) $(CFLAGS) $< -o $@

%.hex : %.out
	$(OBJCOPY) -O ihex $< $@

%.hex : %.s
	$(ASM) $< -o $@	

flash :
	minipro -w $(file) -c code -p $(MINIPRO_DEVICE)

clean :
	rm -f *.hex *.out	
	rm -f *.s.obj
	rm -f *.s.eep.hex
