#define F_CPU 1000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#ifdef DEBUG
#include <avr/include/avr/iom328p.h>
#endif

#include "timer.h"

// borrow from arduino
volatile unsigned long timer0_overflow_count;

long timestamp;

int main(void)
{
  init_timer();
}
