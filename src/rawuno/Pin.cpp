#include <avr/io.h>

#include "Pin.h"

#if 0
/*
 * This code is ugly as fuck, but it's the fastest (?) implementation when
 * arguments are known only at runtime.
 */

void Pin::mode(const uint8_t pin, const PinMode mode) {
  if (mode == OUTPUT) {
    switch (pin) {
      case  0: DDRD |= _BV(DDD0); break;
      case  1: DDRD |= _BV(DDD1); break;
      case  2: DDRD |= _BV(DDD2); break;
      case  3: DDRD |= _BV(DDD3); break;
      case  4: DDRD |= _BV(DDD4); break;
      case  5: DDRD |= _BV(DDD5); break;
      case  6: DDRD |= _BV(DDD6); break;
      case  7: DDRD |= _BV(DDD7); break;

      case  8: DDRC |= _BV(DDC0); break;
      case  9: DDRC |= _BV(DDC1); break;
      case 10: DDRC |= _BV(DDC2); break;
      case 11: DDRC |= _BV(DDC3); break;
      case 12: DDRC |= _BV(DDC4); break;
      case 13: DDRC |= _BV(DDC5); break;

      case 14: DDRB |= _BV(DDB0); break;
      case 15: DDRB |= _BV(DDB1); break;
      case 16: DDRB |= _BV(DDB2); break;
      case 17: DDRB |= _BV(DDB3); break;
      case 18: DDRB |= _BV(DDB4); break;
      case 19: DDRB |= _BV(DDB5); break;

      default: break;
    }
  } else {
    switch (pin) {
      case  0: DDRD &= ~_BV(DDD0); break;
      case  1: DDRD &= ~_BV(DDD1); break;
      case  2: DDRD &= ~_BV(DDD2); break;
      case  3: DDRD &= ~_BV(DDD3); break;
      case  4: DDRD &= ~_BV(DDD4); break;
      case  5: DDRD &= ~_BV(DDD5); break;
      case  6: DDRD &= ~_BV(DDD6); break;
      case  7: DDRD &= ~_BV(DDD7); break;

      case  8: DDRC &= ~_BV(DDC0); break;
      case  9: DDRC &= ~_BV(DDC1); break;
      case 10: DDRC &= ~_BV(DDC2); break;
      case 11: DDRC &= ~_BV(DDC3); break;
      case 12: DDRC &= ~_BV(DDC4); break;
      case 13: DDRC &= ~_BV(DDC5); break;

      case 14: DDRB &= ~_BV(DDB0); break;
      case 15: DDRB &= ~_BV(DDB1); break;
      case 16: DDRB &= ~_BV(DDB2); break;
      case 17: DDRB &= ~_BV(DDB3); break;
      case 18: DDRB &= ~_BV(DDB4); break;
      case 19: DDRB &= ~_BV(DDB5); break;

      default: break;
    }
  }

  Pin::write(pin, mode == INPUT_PULLUP);
}

bool Pin::read(const uint8_t pin) {
  switch (pin) {
    case 0: return bit_is_set(PIND, PIN0);
    case 1: return bit_is_set(PIND, PIN1);
    case 2: return bit_is_set(PIND, PIN2);
    case 3: return bit_is_set(PIND, PIN3);
    case 4: return bit_is_set(PIND, PIN4);
    case 5: return bit_is_set(PIND, PIN5);
    case 6: return bit_is_set(PIND, PIN6);
    case 7: return bit_is_set(PIND, PIN7);

    case 8: return bit_is_set(PINC, PIN0);
    case 9: return bit_is_set(PINC, PIN1);
    case 10: return bit_is_set(PINC, PIN2);
    case 11: return bit_is_set(PINC, PIN3);
    case 12: return bit_is_set(PINC, PIN4);
    case 13: return bit_is_set(PINC, PIN5);

    case 14: return bit_is_set(PINB, PIN0);
    case 15: return bit_is_set(PINB, PIN1);
    case 16: return bit_is_set(PINB, PIN2);
    case 17: return bit_is_set(PINB, PIN3);
    case 18: return bit_is_set(PINB, PIN4);
    case 19: return bit_is_set(PINB, PIN5);

    default: return false;
  }
}

void Pin::write(const uint8_t pin, const bool value) {
  if (value) {
    switch (pin) {
      case  0: PORTD |= _BV(PD0); break;
      case  1: PORTD |= _BV(PD1); break;
      case  2: PORTD |= _BV(PD2); break;
      case  3: PORTD |= _BV(PD3); break;
      case  4: PORTD |= _BV(PD4); break;
      case  5: PORTD |= _BV(PD5); break;
      case  6: PORTD |= _BV(PD6); break;
      case  7: PORTD |= _BV(PD7); break;

      case  8: PORTC |= _BV(PC0); break;
      case  9: PORTC |= _BV(PC1); break;
      case 10: PORTC |= _BV(PC2); break;
      case 11: PORTC |= _BV(PC3); break;
      case 12: PORTC |= _BV(PC4); break;
      case 13: PORTC |= _BV(PC5); break;

      case 14: PORTB |= _BV(PB0); break;
      case 15: PORTB |= _BV(PB1); break;
      case 16: PORTB |= _BV(PB2); break;
      case 17: PORTB |= _BV(PB3); break;
      case 18: PORTB |= _BV(PB4); break;
      case 19: PORTB |= _BV(PB5); break;

      default: break;
    }
  } else {
    switch (pin) {
      case  0: PORTD &= ~_BV(PD0); break;
      case  1: PORTD &= ~_BV(PD1); break;
      case  2: PORTD &= ~_BV(PD2); break;
      case  3: PORTD &= ~_BV(PD3); break;
      case  4: PORTD &= ~_BV(PD4); break;
      case  5: PORTD &= ~_BV(PD5); break;
      case  6: PORTD &= ~_BV(PD6); break;
      case  7: PORTD &= ~_BV(PD7); break;

      case  8: PORTC &= ~_BV(PC0); break;
      case  9: PORTC &= ~_BV(PC1); break;
      case 10: PORTC &= ~_BV(PC2); break;
      case 11: PORTC &= ~_BV(PC3); break;
      case 12: PORTC &= ~_BV(PC4); break;
      case 13: PORTC &= ~_BV(PC5); break;

      case 14: PORTB &= ~_BV(PB0); break;
      case 15: PORTB &= ~_BV(PB1); break;
      case 16: PORTB &= ~_BV(PB2); break;
      case 17: PORTB &= ~_BV(PB3); break;
      case 18: PORTB &= ~_BV(PB4); break;
      case 19: PORTB &= ~_BV(PB5); break;

      default: break;
    }
  }
}
#endif

void Pin::shiftOut(uint8_t dataPin, uint8_t clkPin, BitOrder bitOrder,
                   uint8_t value)
{
  if (bitOrder == LSBFIRST) {
    for (int8_t i = 0; i < 8; i++) {
      Pin::write(dataPin, (value & _BV(i)) ? 1 : 0);
      Pin::write(clkPin, 1);
      Pin::write(clkPin, 0);		
    }
  } else {
    for (int8_t i = 7; i >= 0; i--) {
      Pin::write(dataPin, (value & _BV(i)) ? 1 : 0);
      Pin::write(clkPin, 1);
      Pin::write(clkPin, 0);		
    }
  }
}

uint8_t Pin::shiftIn(uint8_t dataPin, uint8_t clkPin, BitOrder bitOrder) {
	uint8_t value = 0;

  if (bitOrder == LSBFIRST) {
    for (int8_t i = 0; i < 8; i++) {
      Pin::write(clkPin, 1);
      value |= Pin::read(dataPin) << i;
      Pin::write(clkPin, 0);
    }
  } else {
    for (int8_t i = 7; i >= 0; i--) {
      Pin::write(clkPin, 1);
      value |= Pin::read(dataPin) << i;
      Pin::write(clkPin, 0);
    }
  }

	return value;
}
