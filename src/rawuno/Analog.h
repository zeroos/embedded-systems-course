#ifndef __RAWUNO_ANALOG__
#define __RAWUNO_ANALOG__

#include "Pin.h"

namespace Analog {
  typedef enum {
    REF_EXTERNAL = 0, 
    REF_DEFAULT  = _BV(REFS0),
    REF_1V1      = _BV(REFS1) | _BV(REFS0)
  } VoltageRef;

  typedef enum {
    ADC0        = 0,
    ADC1        = _BV(MUX0),
    ADC2        = _BV(MUX1),
    ADC3        = _BV(MUX1) | _BV(MUX0),
    ADC4        = _BV(MUX2),
    ADC5        = _BV(MUX2) | _BV(MUX0),
    ADC6        = _BV(MUX2) | _BV(MUX1),
    ADC7        = _BV(MUX2) | _BV(MUX1) | _BV(MUX0),
    TEMPERATURE = _BV(MUX3),
    GROUND      = _BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0)
  } Input;

  typedef enum {
    CLK_DIV2   = _BV(ADPS0),
    CLK_DIV4   = _BV(ADPS1),
    CLK_DIV8   = _BV(ADPS1) | _BV(ADPS0),
    CLK_DIV16  = _BV(ADPS2),
    CLK_DIV32  = _BV(ADPS2) | _BV(ADPS0),
    CLK_DIV64  = _BV(ADPS2) | _BV(ADPS1),
    CLK_DIV128 = _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0)
  } Clock;

  void init();
  bool selectInput(Input channel, VoltageRef ref = REF_DEFAULT);
  int16_t read();

  void shutdown();
  void wakeup();
};

#endif
