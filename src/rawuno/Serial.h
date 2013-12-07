#ifndef __RAWUNO_SERIAL_H__
#define __RAWUNO_SERIAL_H__

#include "Common.h"

namespace Serial {
  const int16_t FrameError  = -1 << 8;
  const int16_t DataOverRun = -2 << 8;
  const int16_t ParityError = -3 << 8;

  void init(const uint32_t baud = 9600);
  void attachStdIO();

  int16_t recvByte();
  int16_t sendByte(uint8_t data);

  /* power management functions */
  void shutdown();
  void wakeup();
};

#endif
