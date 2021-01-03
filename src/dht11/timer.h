#include <avr/interrupt.h>
#include <avr/io.h>
#ifdef DEBUG
#include <avr/include/avr/iom328p.h>
#endif

volatile unsigned long timer0_overflow_count;

void init_timer();
volatile long time_diff();