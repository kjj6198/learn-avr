#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>
#ifdef DEBUG
#include <avr/include/avr/iom328p.h>
#endif

int main(void)
{
  DDRB = (1 << DDB0);     // set PORTB0 as output and port1 ~ 7 as ouput. DDR means data direction register
  PORTB = (1 << PORTB0);  // set PORTB0 to 1 (HIGH)
  unsigned char i = PINB; // read pin from PINB register
  return 0;
}