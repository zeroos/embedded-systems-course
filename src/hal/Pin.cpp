#include <avr/io.h>

#include "Pin.h"

/*
 * This code is ugly as fuck, but it's the fastest (?) implementation when
 * arguments are known only at runtime.
 */

void Pin::mode(uint8_t pin, PinMode mode) {
  if (mode == OUTPUT) {
    switch (pin) {
      case  0: bset(DDRD, DDD0); break;
      case  1: bset(DDRD, DDD1); break;
      case  2: bset(DDRD, DDD2); break;
      case  3: bset(DDRD, DDD3); break;
      case  4: bset(DDRD, DDD4); break;
      case  5: bset(DDRD, DDD5); break;
      case  6: bset(DDRD, DDD6); break;
      case  7: bset(DDRD, DDD7); break;

      case  8: bset(DDRC, DDC0); break;
      case  9: bset(DDRC, DDC1); break;
      case 10: bset(DDRC, DDC2); break;
      case 11: bset(DDRC, DDC3); break;
      case 12: bset(DDRC, DDC4); break;
      case 13: bset(DDRC, DDC5); break;

      case 14: bset(DDRB, DDB0); break;
      case 15: bset(DDRB, DDB1); break;
      case 16: bset(DDRB, DDB2); break;
      case 17: bset(DDRB, DDB3); break;
      case 18: bset(DDRB, DDB4); break;
      case 19: bset(DDRB, DDB5); break;

      default: break;
    }
  } else {
    switch (pin) {
      case  0: bclr(DDRD, DDD0); break;
      case  1: bclr(DDRD, DDD1); break;
      case  2: bclr(DDRD, DDD2); break;
      case  3: bclr(DDRD, DDD3); break;
      case  4: bclr(DDRD, DDD4); break;
      case  5: bclr(DDRD, DDD5); break;
      case  6: bclr(DDRD, DDD6); break;
      case  7: bclr(DDRD, DDD7); break;

      case  8: bclr(DDRC, DDC0); break;
      case  9: bclr(DDRC, DDC1); break;
      case 10: bclr(DDRC, DDC2); break;
      case 11: bclr(DDRC, DDC3); break;
      case 12: bclr(DDRC, DDC4); break;
      case 13: bclr(DDRC, DDC5); break;

      case 14: bclr(DDRB, DDB0); break;
      case 15: bclr(DDRB, DDB1); break;
      case 16: bclr(DDRB, DDB2); break;
      case 17: bclr(DDRB, DDB3); break;
      case 18: bclr(DDRB, DDB4); break;
      case 19: bclr(DDRB, DDB5); break;

      default: break;
    }
  }

  write(pin, mode == INPUT_PULLUP);
}

bool Pin::read(uint8_t pin) {
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

void Pin::write(uint8_t pin, bool value) {
  if (value) {
    switch (pin) {
      case  0: bset(PORTD, PD0); break;
      case  1: bset(PORTD, PD1); break;
      case  2: bset(PORTD, PD2); break;
      case  3: bset(PORTD, PD3); break;
      case  4: bset(PORTD, PD4); break;
      case  5: bset(PORTD, PD5); break;
      case  6: bset(PORTD, PD6); break;
      case  7: bset(PORTD, PD7); break;

      case  8: bset(PORTC, PC0); break;
      case  9: bset(PORTC, PC1); break;
      case 10: bset(PORTC, PC2); break;
      case 11: bset(PORTC, PC3); break;
      case 12: bset(PORTC, PC4); break;
      case 13: bset(PORTC, PC5); break;

      case 14: bset(PORTB, PB0); break;
      case 15: bset(PORTB, PB1); break;
      case 16: bset(PORTB, PB2); break;
      case 17: bset(PORTB, PB3); break;
      case 18: bset(PORTB, PB4); break;
      case 19: bset(PORTB, PB5); break;

      default: break;
    }
  } else {
    switch (pin) {
      case  0: bclr(PORTD, PD0); break;
      case  1: bclr(PORTD, PD1); break;
      case  2: bclr(PORTD, PD2); break;
      case  3: bclr(PORTD, PD3); break;
      case  4: bclr(PORTD, PD4); break;
      case  5: bclr(PORTD, PD5); break;
      case  6: bclr(PORTD, PD6); break;
      case  7: bclr(PORTD, PD7); break;

      case  8: bclr(PORTC, PC0); break;
      case  9: bclr(PORTC, PC1); break;
      case 10: bclr(PORTC, PC2); break;
      case 11: bclr(PORTC, PC3); break;
      case 12: bclr(PORTC, PC4); break;
      case 13: bclr(PORTC, PC5); break;

      case 14: bclr(PORTB, PB0); break;
      case 15: bclr(PORTB, PB1); break;
      case 16: bclr(PORTB, PB2); break;
      case 17: bclr(PORTB, PB3); break;
      case 18: bclr(PORTB, PB4); break;
      case 19: bclr(PORTB, PB5); break;

      default: break;
    }
  }
}

void Pin::shiftOut(uint8_t dataPin, uint8_t clkPin, BitOrder bitOrder,
                   uint8_t value)
{
  if (bitOrder == LSBFIRST) {
    for (int8_t i = 0; i < 8; i++) {
      write(dataPin, value & _BV(i));
      write(clkPin, 1);
      write(clkPin, 0);		
    }
  } else {
    for (int8_t i = 7; i >= 0; i--) {
      write(dataPin, value & _BV(i));
      write(clkPin, 1);
      write(clkPin, 0);		
    }
  }
}

uint8_t Pin::shiftIn(uint8_t dataPin, uint8_t clkPin, BitOrder bitOrder) {
  uint8_t value = 0;

  if (bitOrder == LSBFIRST) {
    for (int8_t i = 0; i < 8; i++) {
      write(clkPin, 1);
      value |= read(dataPin) << i;
      write(clkPin, 0);
    }
  } else {
    for (int8_t i = 7; i >= 0; i--) {
      write(clkPin, 1);
      value |= read(dataPin) << i;
      write(clkPin, 0);
    }
  }

  return value;
}
