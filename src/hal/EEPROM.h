#ifndef __HAL_EEPROM_H__
#define __HAL_EEPROM_H__

#include "Common.h"

#ifndef EEMEM
#define EEMEM __attribute__((section(".eeprom")))
#endif

namespace EEPROM {
  uint8_t read(uint16_t address);
  void write(uint16_t address, uint8_t data);

  template<typename T>
    class Var {
      private:
        uint16_t address() const {
          /* Avrdude cannot program EEPROM with Arduino backend, so we cannot
           * initialize the variable. */
          static EEMEM T var;
          return (uint16_t)&var;
        }

      public:
        void put(T v) const {
          write(address(), v);
        } 

        T get() const {
          return read(address());
        }
    };

  typedef Var<uint8_t> Byte;
};

#endif
