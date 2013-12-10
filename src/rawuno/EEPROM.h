#ifndef __RAWUNO_EEPROM_H__
#define __RAWUNO_EEPROM_H__

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
          static EEMEM T var = 0;
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
