#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "Analog.h"
#include "Pin.h"

/* ADC conversion complete interrupt */
EMPTY_INTERRUPT(ADC_vect);

static Analog::VoltageRef voltageRef = Analog::DEFAULT;

void Analog::setVoltageRef(Analog::VoltageRef ref) {
  voltageRef = ref;
}

int16_t Analog::read(uint8_t pin) {
  if (pin >= A0)
    pin -= A0;

  if (pin < 6) {
    /* Set up pin mode */
    bclr(DDRC, pin);
    bclr(PORTC, pin);
    /* Set up input pin and reference voltage */
    ADMUX = (voltageRef << 6) | pin;
    /* Digital input disable on analog pin. */
    DIDR0 = _BV(pin);
  } else if (pin == BUILTIN_TEMP) {
    /* For builtin temperature sensor 1.1V reference must be selected */
    ADMUX = (INTERNAL << 6) | _BV(MUX3);
  } else {
    return -1;
  }

  uint8_t hi, lo;

  /* Enable ADC and ADC interrupt */
  ADCSRA = _BV(ADIE) | _BV(ADEN);

  /* Start conversion! */
  bset(ADCSRA, ADSC);

  while (bit_is_set(ADCSRA, ADSC))
    sleep_mode();

  lo = ADCL;
  hi = ADCH;

  return (hi << 8) | lo;
}

void Analog::shutdown() {
  /* Disable ADC before shutdown */
  bclr(ADCSRA, ADEN);
  bset(PRR, PRADC);
}

void Analog::wakeup() {
  bclr(PRR, PRADC);
}
