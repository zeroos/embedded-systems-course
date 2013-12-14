#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "Analog.h"
#include "Pin.h"

/* ADC conversion complete interrupt */
EMPTY_INTERRUPT(ADC_vect);

void Analog::init() {
  ADMUX = GROUND | REF_DEFAULT;
  ADCSRA = _BV(ADEN) | _BV(ADIE) | _BV(ADSC) | CLK_DIV128;

  /* Interrupts are not enabled yet! */
  while (bget(ADCSRA, ADSC));
}

bool Analog::selectInput(Input channel, VoltageRef ref) {
  if (channel <= ADC7) {
    /* Set up input pin and reference voltage */
    ADMUX = ref | channel;
    /* Digital input disable on analog pin. */
    DIDR0 = channel;
  } else if (channel == TEMPERATURE) {
    /* For builtin temperature sensor 1.1V reference must be selected */
    ADMUX = REF_1V1 | channel;
  } else {
    return false;
  }

  return true;
}

int16_t Analog::read() {
  uint8_t hi, lo;

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
