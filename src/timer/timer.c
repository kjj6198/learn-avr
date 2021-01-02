#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifdef DEBUG
#include <avr/include/avr/iom328p.h>
#endif

// example for using ATMEGA timer interrupt
// LED blinks every one second without blocking CPU
int main(void)
{
  DDRB = 0x01;
  PORTB = 0;
  cli();
  TCCR1B = (1 << CS11) | (1 << CS10) | (1 << WGM12); // ctc mode + clk/64
  OCR1A = 15624;                                     // every one second
  TIMSK1 = 1 << OCIE1A;
  sei();

  while (1)
  {
  }
}

ISR(TIMER1_COMPA_vect)
{
  PORTB ^= (1 << PORTB0);
}