#ifndef __RAWUNO_ANALOG__
#define __RAWUNO_ANALOG__

#include "Pin.h"

#define BUILTIN_TEMP 8

namespace Analog {
  typedef enum { DEFAULT = 1, EXTERNAL = 0, INTERNAL = 3 } VoltageRef;

  void setVoltageRef(VoltageRef ref);
  int16_t read(uint8_t pin);

  void shutdown();
  void wakeup();
};

#endif
