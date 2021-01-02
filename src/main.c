#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  DDRB = 0x01;
  PORTB = 0;
  while (1)
  {
    PORTB = 0x01;
    _delay_ms(10);
    PORTB = 0;
    _delay_ms(10);
  }
}