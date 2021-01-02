// F_CPU and BAUD will be used in setbaud.h so define them first
#define F_CPU 1000000L
#define BAUD 9600

#include <avr/io.h>
#include <util/delay.h>

// setbaud is an util for calculating baud rate
// it'll set UBRRH, UBRRL value for you
#include <util/setbaud.h>
#include <avr/interrupt.h>

#ifdef DEBUG
#include <avr/include/avr/iom328p.h>
#endif

volatile int should_turn_off = 0;

inline static void init_timer(void)
{
  cli();
  TCCR1B = (1 << CS11) | (1 << CS10) | (1 << WGM12); // ctc mode + clk/64
  OCR1A = 15624;
  TIMSK1 = 1 << OCIE1A;
  sei();
}

inline static void stop_timer(void)
{
  TIMSK1 &= ~(1 << OCIE1A);
  TCNT1 = 0;
}

void transmit_byte(uint8_t data)
{
  loop_until_bit_is_set(UCSR0A, UDRE0);
  /*
   * all you need to do is just put data into register, atmega will send data for you in the right time
   * USART can only send 7 ~ 9 bit per time, if you want to send string, you have to store it in buffer first
   */
  UDR0 = data;
}

void print_string(const char myString[])
{
  uint8_t i = 0;
  while (myString[i])
  {
    transmit_byte(myString[i]);
    i++;
  }
}

int main(void)
{
  DDRB = 1 << DDB0;
  PORTB = 0;

  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
#if USE_2X
  UCSR0A |= (1 << U2X0);
#else
  UCSR0A &= ~(1 << U2X0);
#endif
  UCSR0B = 1 << (TXEN0) | 1 << (TXCIE0);
  UCSR0C = 1 << UCSZ01 | 1 << UCSZ00;
  sei();
  while (1)
  {
    print_string("Hello From ATMEGA328p");
    _delay_ms(1000);
  }
}

ISR(USART_TX_vect)
{
  // still waiting, reschedule
  if (should_turn_off == 1)
  {
  }
  else
  {
    PORTB = 1;
    should_turn_off = 1;
    init_timer();
  }
}

ISR(TIMER1_COMPA_vect)
{
  if (should_turn_off)
  {
    PORTB = 0;
    should_turn_off = 0;
    stop_timer();
  }
}