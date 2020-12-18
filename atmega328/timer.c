#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#ifdef DEBUG
#include <avr/include/avr/iom328p.h>
#endif

int extraTime = 0;

int main(void)
{
  DDRB = 0x01;
  PORTB = 0;
  TCCR0A = 1 << WGM01;
  OCR0A = 255;
  TIMSK0 = 1 << OCIE0A;
  sei();
  TCCR0B = 1 << CS02 | 1 << CS00;

  while (1)
  {
  }
}

ISR(TIMER0_COMPA_vect)
{
  extraTime++;
  if (extraTime > 100)
  {
    PORTB ^= (1 << PORTB0);
  }
}