#ifndef __HAL_PIN_H__
#define __HAL_PIN_H__

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
typedef enum { MSBFIRST, LSBFIRST } BitOrder;

namespace Pin {
  template <int PIN>
  struct Pin {
    void mode(PinMode mode) const {
      if (PIN < 8) {
        bput(DDRD, PIN, mode == OUTPUT);
        bput(PORTD, PIN, mode == INPUT_PULLUP);
      } else if (PIN < 14) {
        bput(DDRB, PIN - 8, mode == OUTPUT);
        bput(PORTB, PIN - 8, mode == INPUT_PULLUP);
      } else if (PIN < 20) {
        bput(DDRC, PIN - 14, mode == OUTPUT);
        bput(PORTC, PIN - 14, mode == INPUT_PULLUP);
      }
    }

    inline bool read() const {
      if (PIN < 8)
        return bget(PIND, PIN);
      else if (PIN < 14)
        return bget(PINB, PIN - 8);
      else if (PIN < 20)
        return bget(PINC, PIN - 14);
      return false;
    }

    inline void high() const {
      if (PIN < 8)
        bset(PORTD, PIN);
      else if (PIN < 14)
        bset(PORTB, PIN - 8);
      else if (PIN < 20)
        bset(PORTC, PIN - 14);
    }

    inline void low() const {
      if (PIN < 8)
        bclr(PORTD, PIN);
      else if (PIN < 14)
        bclr(PORTB, PIN - 8);
      else if (PIN < 20)
        bclr(PORTC, PIN - 14);
    }

    inline void toggle() const {
      if (read()) low(); else high();
    }

    inline void write(bool value) const {
      if (value) high(); else low();
    }

    template <int CLK>
    void shiftOut(Pin<CLK> clock, BitOrder bitOrder, uint8_t value) const
    {
      if (bitOrder == LSBFIRST) {
        for (int8_t i = 0; i < 8; i++) {
          write(bget(value, i));
          clock.high();
          clock.low();		
        }
      } else {
        for (int8_t i = 7; i >= 0; i--) {
          write(bget(value, i));
          clock.high();
          clock.low();
        }
      }
    }

    template <int CLK>
    uint8_t shiftIn(Pin<CLK> clock, BitOrder bitOrder) const
    {
      uint8_t value = 0;

      if (bitOrder == LSBFIRST) {
        for (int8_t i = 0; i < 8; i++) {
          clock.high();
          value |= read() << i;
          clock.low();
        }
      } else {
        for (int8_t i = 7; i >= 0; i--) {
          clock.high();
          value |= read() << i;
          clock.low();
        }
      }

      return value;
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
