#ifndef __RAWUNO_PIN_H__
#define __RAWUNO_PIN_H__

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
typedef enum { MSBFIRST, LSBFIRST } BitOrder;

namespace Pin {
  template <int PIN>
  struct Pin {
    void mode(PinMode mode) {
      if (PIN < 8) {
        bit_set(DDRD, PIN, mode == OUTPUT);
        bit_set(PORTD, PIN, mode == INPUT_PULLUP);
      } else if (PIN < 14) {
        bit_set(DDRB, PIN - 8, mode == OUTPUT);
        bit_set(PORTB, PIN - 8, mode == INPUT_PULLUP);
      } else if (PIN < 20) {
        bit_set(DDRC, PIN - 14, mode == OUTPUT);
        bit_set(PORTC, PIN - 14, mode == INPUT_PULLUP);
      }
    }

    bool read() {
      bool value = false;

      if (PIN < 8) {
        value = bit_is_set(PIND, PIN);
      } else if (PIN < 14) {
        value = bit_is_set(PINB, PIN - 8);
      } else if (PIN < 20) {
        value = bit_is_set(PINC, PIN - 14);
      }

      return value;
    }

    void write(bool value) {
      if (PIN < 8) {
        bit_set(PORTD, PIN, value);
      } else if (PIN < 14) {
        bit_set(PORTB, PIN - 8, value);
      } else if (PIN < 20) {
        bit_set(PORTC, PIN - 14, value);
      }
    }
  };

  void mode(uint8_t pin, PinMode mode);
  bool read(uint8_t pin);
  void write(uint8_t pin, bool value);
  void shiftOut(uint8_t dataPin, uint8_t clockPin, BitOrder bitOrder,
                uint8_t value);
  uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, BitOrder bitOrder);
};

#endif
