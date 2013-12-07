#ifndef __RAWUNO_SERIAL_H__
#define __RAWUNO_SERIAL_H__

#include <avr/io.h>
#include <stdint.h>

namespace Serial {
  const int16_t FrameError  = -1 << 8;
  const int16_t DataOverRun = -2 << 8;
  const int16_t ParityError = -3 << 8;

  void init(const uint32_t baud = 9600);
  void attach_stdio();

  int16_t recv_byte();
  int16_t send_byte(uint8_t data);
};

#endif
