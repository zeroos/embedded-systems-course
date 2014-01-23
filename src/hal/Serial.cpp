#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/atomic.h>
#include <stdio.h>

#include "Serial.h"

/* RX complete interrupt */
EMPTY_INTERRUPT(USART_RX_vect);
/* TX complete interrupt */
EMPTY_INTERRUPT(USART_TX_vect);

/* TODO: read UDR0 and UCSR0A directly in interrupt handler */
int16_t Serial::recvByte() {
  /* Wait for data to be received */
  while (bit_is_clear(UCSR0A, RXC0))
    sleep_mode();

  /* Check for errors */
  if (bit_is_set(UCSR0A, FE0))
    return Serial::FrameError;
  if (bit_is_set(UCSR0A, DOR0))
    return Serial::DataOverRun;
  if (bit_is_set(UCSR0A, UPE0))
    return Serial::ParityError;

  /* Read the buffer into register */
  uint8_t byte = UDR0;

  /* Return received data */
  return byte;
}

int16_t Serial::sendByte(uint8_t byte) {
  /* Wait for empty transmit buffer */
  while (bit_is_clear(UCSR0A, UDRE0))
    sleep_mode();

  /* Put data into buffer to send the data */
  UDR0 = byte;

  return 0;
}

static int ser_putc(char c, FILE *stream UNUSED) {
  /* Always put CR character after LF */
  if (c == '\n')
    if (Serial::sendByte('\r') < 0)
      return EOF;

  return (Serial::sendByte(c) < 0) ? EOF : 0;
}

static int ser_getc(FILE *stream UNUSED) {
  int c = Serial::recvByte();

  if (c < 0)
    return EOF;
  
  return c;
}

static FILE ser_io;

void Serial::attachStdIO() {
  fdev_setup_stream(&ser_io, ser_putc, ser_getc, _FDEV_SETUP_RW);

  stdout = stdin = &ser_io;
}

void Serial::shutdown() {
  bset(PRR, PRUSART0);
}

void Serial::wakeup() {
  bclr(PRR, PRUSART0);
}
