CC = avr-gcc
CFLAGS += -O2 -Wall -mmcu=atmega328p
OBJCOPY = avr-objcopy
MINIPRO_DEVICE = ATMEGA328P@DIP28

%.out: %.c
	$(CC) $(CFLAGS) $< -o $@

%.hex : %.out
	$(OBJCOPY) -O ihex $< $@

flash :
	minipro -w $(file) -c code -p $(MINIPRO_DEVICE)

clean :
	rm -f *.hex *.out	
