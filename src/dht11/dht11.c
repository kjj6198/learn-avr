#define F_CPU 1000000L
#define BAUD 9600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/setbaud.h>
#ifdef DEBUG
#include <avr/include/avr/iom328p.h>
#endif

#define DHT_HOST_START 0
#define DHT_HOST_PULLUP 1
#define DHT_WAIT_RESPONSE 2
#define DHT_PULLUP 3
#define DHT_TRANSFERING 4
#define DHT_CHECK_CRC 5

#include "timer.h"

int state = DHT_HOST_START;
uint16_t raw_humidity = 0;
uint16_t raw_temperature = 0;
uint8_t checksum = 0;
volatile int bit_count;
long timestamp = 0;

// borrow from arduino
volatile unsigned long timer0_overflow_count;

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

void read_dht()
{
  DDRD |= 1 << DDD2;
  cli();
  state = DHT_HOST_START;
  TCCR1B = 1 << CS10 | 1 << WGM12;
  OCR1A = 18000; // 18ms
  TIMSK1 = 1 << OCIE1A;
  PORTD = ~(1 << PORTD2); // 0 for 18ms
  sei();
}

int main(void)
{
  bit_count = 0;
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
#if USE_2X
  UCSR0A |= (1 << U2X0);
#else
  UCSR0A &= ~(1 << U2X0);
#endif
  UCSR0B = 1 << (TXEN0) | 1 << (TXCIE0);
  UCSR0C = 1 << UCSZ01 | 1 << UCSZ00;

  while (1)
  {
    _delay_ms(2500);
    DDRD |= 1 << DDD2;
    PORTD = 1 << PORTD2;
    _delay_ms(1000);
    PORTD = ~(1 << PORTD2);
    _delay_ms(18);
    PORTD = 1 << PORTD2;
    _delay_us(40);
    DDRD = ~(1 << DDD2);
    EIMSK = ~(1 << INT0);
    EICRA = 1 << ISC00;
    EIMSK = 1 << INT0;
    sei();
    transmit_byte(bit_count);
    _delay_ms(2500);
  }

  return 0;
}

// ISR(TIMER1_COMPA_vect)
// {
//   if (state == DHT_HOST_START)
//   {
//     DDRD |= 1 << DDD2;
//     PORTD = (1 << PORTD2);
//     TCNT1 = 0;
//     OCR1A = 40;
//     state = DHT_HOST_PULLUP;
//     return;
//   }
//   else if (state == DHT_HOST_PULLUP)
//   {
//     DDRD = ~(1 << DDD2);
//     PORTD = 1 << PORTD2;
//     EIMSK = ~(1 << INT0);
//     EICRA = 1 << ISC00;
//     EIMSK = 1 << INT0;
//     state = DHT_WAIT_RESPONSE;
//     bit_count = 0;
//     timestamp = time_diff();
//     return;
//   }
// }

ISR(INT0_vect)
{
  // long counter_us;
  counter_us = time_diff() - timestamp;
  transmit_byte(bit_count);
  bit_count++;
  if (state == DHT_WAIT_RESPONSE && (counter_us > 40) && (counter_us < 100))
  {
    EIMSK = ~(1 << INT0);
    EICRA = 1 << ISC01 | ~(1 << ISC00);
    EIMSK = 1 << INT0;
    state = DHT_PULLUP;
  }
  else if (state == DHT_PULLUP && (counter_us > 60) && (counter_us < 100))
  {
    state = DHT_TRANSFERING;
    return;
  }
  else if (state == DHT_TRANSFERING && (counter_us > 50) && (counter_us <= 110))
  {
    bit_count++;
  }
  else if (state == DHT_TRANSFERING && (counter_us > 110) && (counter_us <= 160))
  {
    if (bit_count < 16)
    {
      raw_humidity |= (1 << (15 - bit_count));
    }
    if (bit_count >= 16 && bit_count < 32)
    {
      raw_temperature |= (1 << (31 - bit_count));
    }

    if (bit_count >= 32 && bit_count < 40)
    {
      checksum |= (1 << (39 - bit_count));
    }
    bit_count++;
  }

  if (bit_count > 39)
  {
    EIMSK = ~(1 << INT0);
    DDRD |= 1 << DDD2;
    PORTD |= 1 << PORTD2;  // 0 for 18ms
    bit_count = 0;         // Reset bit counter.
    state = DHT_CHECK_CRC; // Change state.
  }
}