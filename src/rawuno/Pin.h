#ifndef __RAWUNO_PIN_H__
#define __RAWUNO_PIN_H__

#include <stdint.h>
#include <avr/io.h>

#define A0 14
#define A1 15
#define A2 16
#define A3 17
#define A4 18
#define A5 19

template <int PIN>
struct Pin {
  static bool read(void) {
    bool value = false;

    if (PIN < 8) {
      DDRD &= ~_BV(PIN);
      value = bit_is_set(PIND, PIN);
    } else if (PIN < 14) {
      DDRB &= ~_BV(PIN - 8);
      value = bit_is_set(PINB, PIN - 8);
    } else if (PIN < 20) {
      DDRC &= ~_BV(PIN - 14);
      value = bit_is_set(PINC, PIN - 14);
    }

    return value;
  }

  static void write(bool value) {
    if (PIN < 8) {
      DDRD |= _BV(PIN);
      if (value)
        PIND |= _BV(PIN);
      else
        PIND &= ~_BV(PIN);
    } else if (PIN < 14) {
      DDRB |= _BV(PIN - 8);
      if (value)
        PINB |= _BV(PIN - 8);
      else
        PINB &= ~_BV(PIN - 8);
    } else if (PIN < 20) {
      DDRC |= _BV(PIN - 14);
      if (value)
        PINC |= _BV(PIN - 14);
      else
        PINC &= ~_BV(PIN - 14);
    }
  }
};

#endif
