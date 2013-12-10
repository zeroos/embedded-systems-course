#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/atomic.h>

#include "Timer0.h"
#include "sintab.h"

ISR(TIMER0_OVF_vect) {
  static uint8_t diff = 1;
  static uint8_t value = 1;

  value += diff;

  if (value == 255)
    diff = -1;
  if (value == 1)
    diff = 1;

  Timer0::counter(0);
  Timer0::compareA(sintab[value]);
}

int main() {
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    Timer0::modeSelect(Timer0::FAST_PWM, Timer0::CLEAR_ON_MATCH_A, Timer0::DISABLE_B);
    Timer0::clockSelect(Timer0::CLK_BY_256);
    Timer0::enableInterrupt(Timer0::OVERFLOW);

    /* Set initial counter and compare values */
    Timer0::counter(0);
    Timer0::compareA(1);
  }

  while (true)
    sleep_mode();

  return 0;
}
