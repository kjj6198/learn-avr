#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>
#ifdef DEBUG
#include <avr/include/avr/iom328p.h>
#endif

// borrow from arduino
extern volatile unsigned long timer0_overflow_count;

#define MAX_CYCLES 70
#define MIN_CYCLES 26

#define DHT_PIN PORTB0
#define data_size 40;

long timestamp;

int i;
int data[40];

void send_signal()
{
  DDRB |= 1 << DHT_PIN;
  PORTB |= 0 << DHT_PIN;
  _delay_ms(18);
  PORTB = 1 << DHT_PIN;
  DDRB = ~(1 << DHT_PIN);
  timestamp = time_diff();
}

void read_data()
{
  cli();
  PCICR = 1 << PCIE0; // pin change interrupt enable 0
  PCMSK0 = 1 << PCINT0;
  sei();
}

void init_timer()
{
  cli();
  TCNT0 = 0;
  TIMSK0 = 1 << TOIE0;
  sei();
}

int main(void)
{
  init_timer();
  send_signal();
  _delay_ms(200);
}

int time_diff()
{
  return timer0_overflow_count * 256 + TCNT0;
}

ISR(TIMER0_OVF_vect)
{
  timer0_overflow_count++;
}

ISR(PCINT0_vect)
{
  if (PCIF0 == 1 && PINB0 == 1)
  {
    long diff = time_diff() - timestamp;
    if (diff >= 74 && diff <= 80)
    {
      // print start to transmit 1-bit data
    }
    else if (diff >= 50 && diff < 60)
    {
      // wait
    }
  }
  else if (PCIF0 == 1 && PINB0 == 0)
  {
    long diff = time_diff() - timestamp; // start time
    if (diff > 74 && diff <= 80)
    {
      i = 0;
      // print pulls up
    }
    else if (diff > 60 && diff <= 71)
    {
      data[i] = 1;
      i++;
    }
    else if (diff < 60)
    {
      data[i] = 0;
      i++;
    }
  }

  if (i == 40)
  {
    // trigger measure completed interrupts
  }

  timestamp = time_diff();
}