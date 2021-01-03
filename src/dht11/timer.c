#include "timer.h"

long timestamp;

void init_timer()
{
  timer0_overflow_count = 0;
  cli();
  TCNT0 = 0;
  TCCR0B = 1 << CS00;
  TIMSK0 = 1 << TOV0;
  sei();
}

volatile long time_diff()
{
  return timer0_overflow_count * (1 << 8) + TCNT0;
}

ISR(TIMER0_OVF_vect)
{
  timer0_overflow_count++;
}