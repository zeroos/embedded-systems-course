#ifndef __HAL_SPI_H__
#define __HAL_SPI_H__

#include <util/atomic.h>

#include "Common.h"
#include "Pin.h"

namespace SPI {
  typedef enum {
    SLAVE  = 0,
    MASTER = _BV(MSTR)
  } Mode;

  typedef enum {
    CLK_DIV4  = 0,
    CLK_DIV16 = _BV(SPR0 + 1),
    CLK_DIV64 = _BV(SPR1 + 1),
    CLK_DIV128 = _BV(SPR1 + 1) | _BV(SPR0 + 1),
    CLK_DIV2  = _BV(SPI2X),
    CLK_DIV8  = _BV(SPI2X) | _BV(SPR0 + 1),
    CLK_DIV32 = _BV(SPI2X) | _BV(SPR1 + 1)
  } Clock;

  typedef enum {
    MSBFIRST = 0,
    LSBFIRST = _BV(DORD)
  } BitOrder;

  static UNUSED inline void
    init(Mode mode = MASTER, Clock clock = CLK_DIV2, BitOrder order = LSBFIRST)
  {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
      SPCR = _BV(SPE) |  mode | order | (clock >> 1);
      SPSR = clock & 1;

      Pin::Pin<MISO> miso;
      Pin::Pin<MOSI> mosi;
      Pin::Pin<SCK> sck;
      Pin::Pin<SS> ss;

      if (mode) {
        miso.mode(INPUT);
        mosi.mode(OUTPUT);
        sck.mode(OUTPUT);
        ss.mode(OUTPUT);
        ss.high();
      } else {
        miso.mode(OUTPUT);
        mosi.mode(INPUT);
        sck.mode(INPUT);
        ss.mode(INPUT);
      }
    }
  }

  uint8_t transmit(uint8_t data);
};

#endif
