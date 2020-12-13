#define F_CPU 20000000L

#include <avr/io.h>
#include <avr/delay.h>

int main(void)
{
  DDRB = 0x01;
  PORTB = 0;
  while (1)
  {
    PORTB = 0x01;
    _delay_ms(1000);
    PORTB = 0;
    _delay_ms(1000);
  }
}