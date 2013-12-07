#ifndef __RAWUNO_EEPROM_H__
#define __RAWUNO_EEPROM_H__

#include "Common.h"

namespace EEPROM {
  uint8_t read(uint16_t address);
  void write(uint16_t address, uint8_t data);
};

#endif
