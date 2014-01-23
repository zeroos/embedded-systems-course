#ifndef __HAL_SERIAL_H__
#define __HAL_SERIAL_H__

#include <avr/io.h>

#include "Common.h"

namespace Serial {
  const int16_t FrameError  = -1 << 8;
  const int16_t DataOverRun = -2 << 8;
  const int16_t ParityError = -3 << 8;

  template <uint32_t BAUD = 38400>
    inline void init()
  {
    uint16_t ubrr = (F_CPU + 4UL * BAUD) / (8UL * BAUD) - 1UL;

    UBRR0H = ubrr >> 8;
    UBRR0L = ubrr & 0xff;

    /* Improve baud rate error by using 2x clk */
    UCSR0A = _BV(U2X0);
    /* Interrupts enable, TX/RX enable. */
    UCSR0B = _BV(RXCIE0) | _BV(TXCIE0) |  _BV(RXEN0) | _BV(TXEN0);
    /* 8N1 frame format */
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
  }

  void attachStdIO();

  int16_t recvByte();
  int16_t sendByte(uint8_t data);

  /* power management functions */
  void shutdown();
  void wakeup();
};

#endif
