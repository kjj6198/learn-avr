#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  while (1)
  {
    DDRB = (1 << DDB0);     // set PORTB0 as output and port1 ~ 7 as ouput. DDR means data direction register
    PORTB = (1 << PORTB0);  // set PORTB0 to 1 (HIGH)
    unsigned char i = PINB; // read pin from PINB register
    _delay_ms(500);
    PORTB = ~(1 << PORTB0);
    _delay_ms(500);
    bit(PORTB);
  }
  return 0;
}


