#define F_CPU 1000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#ifdef DEBUG
#include <avr/include/avr/iom328p.h>
#endif

// external interrupt
int main(void)
{
  cli();
  DDRD = ~(1 << DDD2);
  PORTD = (1 << PORTD2);
  EICRA = 1 << ISC00;
  EIMSK = 1 << INT0;
  DDRB = 1 << DDB0;
  sei();
  while (1)
  {
  }
}

ISR(INT0_vect)
{
  PORTB ^= 1 << PORTB0;
}