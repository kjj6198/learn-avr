#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <string.h>

#ifdef DEBUG
#include <avr/include/avr/iom328p.h>
#endif

const char str[] PROGMEM = "Hello from flash";

int main(void)
{
  char string[100];
  memset(string, 0, sizeof string);
  while (1)
  {
    for (int i = 0; i < sizeof(str); i++)
    {
      string[i] = pgm_read_byte(&(str[i]));
    }
  }
}