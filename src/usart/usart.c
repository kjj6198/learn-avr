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

void transmitByte(uint8_t data)
{
  /* Wait for empty transmit buffer */
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = data; /* send data */
}

//  Example of a useful printing command
void printString(const char myString[])
{
  uint8_t i = 0;
  while (myString[i])
  {
    transmitByte(myString[i]);
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
    printString("Hello World from atmega328p");
    printString("abc");
    _delay_ms(1000);
  }
}

ISR(USART_TX_vect)
{
  PORTB = 1;
  _delay_ms(1000);
  PORTB = 0;
}