#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/atomic.h>

#include "Serial.h"

/* RX complete interrupt */
EMPTY_INTERRUPT(USART_RX_vect);
/* TX complete interrupt */
EMPTY_INTERRUPT(USART_TX_vect);
/* Data register empty interrupt */
EMPTY_INTERRUPT(USART_UDRE_vect);

void Serial::init(const uint32_t baud) {
  uint16_t ubrr = (F_CPU + 4UL * baud) / (8UL * baud) - 1UL;

  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    UBRR0H = ubrr >> 8;
    UBRR0L = ubrr & 0xff;

    /* Improve baud rate error by using 2x clk */
    UCSR0A = _BV(U2X0);
    /* TX/RX enable */
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);
    /* 8N1 frame format */
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
  }
}

int16_t Serial::recv_byte() {
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

void Serial::send_byte(uint8_t byte) {
  /* Wait for empty transmit buffer */
  while (bit_is_clear(UCSR0A, UDRE0))
    sleep_mode();

  /* Put data into buffer to send the data */
  UDR0 = byte;
}
