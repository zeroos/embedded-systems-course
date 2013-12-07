#ifndef __RAWUNO_PIN_H__
#define __RAWUNO_PIN_H__

#include <avr/io.h>

#include "Common.h"

static const uint8_t RX = 0;
static const uint8_t TX = 1;

static const uint8_t SS = 10;
static const uint8_t MOSI = 11;
static const uint8_t MISO = 12;
static const uint8_t SCK = 13;

static const uint8_t A0 = 14;
static const uint8_t A1 = 15;
static const uint8_t A2 = 16;
static const uint8_t A3 = 17;
static const uint8_t A4 = 18;
static const uint8_t A5 = 19;

static const uint8_t SDA = 18;
static const uint8_t SCL = 19;

typedef enum { INPUT, INPUT_PULLUP, OUTPUT } PinMode;

namespace Pin {
  static UNUSED inline void mode(uint8_t pin, PinMode mode) {
    if (pin < 8) {
      bit_set(DDRD, pin, mode == OUTPUT);
      bit_set(PORTD, pin, mode == INPUT_PULLUP);
    } else if (pin < 14) {
      bit_set(DDRB, pin - 8, mode == OUTPUT);
      bit_set(PORTB, pin - 8, mode == INPUT_PULLUP);
    } else if (pin < 20) {
      bit_set(DDRC, pin - 14, mode == OUTPUT);
      bit_set(PORTC, pin - 14, mode == INPUT_PULLUP);
    }
  }

  static UNUSED inline bool read(uint8_t pin) {
    bool value = false;

    if (pin < 8) {
      value = bit_is_set(PIND, pin);
    } else if (pin < 14) {
      value = bit_is_set(PINB, pin - 8);
    } else if (pin < 20) {
      value = bit_is_set(PINC, pin - 14);
    }

    return value;
  }

  static UNUSED inline void write(uint8_t pin, bool value) {
    if (pin < 8) {
      bit_set(PORTD, pin, value);
    } else if (pin < 14) {
      bit_set(PORTB, pin - 8, value);
    } else if (pin < 20) {
      bit_set(PORTC, pin - 14, value);
    }
  }
};

#endif
