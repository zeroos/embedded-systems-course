#ifndef __RAWUNO_SPI_H__
#define __RAWUNO_SPI_H__

#include "Common.h"

namespace SPI {
  void masterInit();
  void slaveInit();

  uint8_t transmit(uint8_t data);
};

#endif
