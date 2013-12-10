#ifndef __RAWUNO_TIMER0_H__
#define __RAWUNO_TIMER0_H__

#include "Common.h"

namespace Timer0 {
  typedef enum {
    NORMAL            = 0,
    CTC               = _BV(WGM01),
    FAST_PWM          = _BV(WGM01) | _BV(WGM00),
    PHASE_CORRECT_PWM = _BV(WGM00)
  } Mode;

  typedef enum {
    DISABLE_A         = 0,
    TOGGLE_ON_MATCH_A = _BV(COM0A0),
    CLEAR_ON_MATCH_A  = _BV(COM0A1),
    SET_ON_MATCH_A    = _BV(COM0A1) | _BV(COM0A0)
  } OutputA;

  typedef enum {
    DISABLE_B         = 0,
    TOGGLE_ON_MATCH_B = _BV(COM0B0),
    CLEAR_ON_MATCH_B  = _BV(COM0B1),
    SET_ON_MATCH_B    = _BV(COM0B1) | _BV(COM0B0)
  } OutputB;

  typedef enum {
    CLK_STOP    = 0,
    CLK_NORMAL  = _BV(CS00),
    CLK_BY_8    = _BV(CS01),
    CLK_BY_64   = _BV(CS01) | _BV(CS00),
    CLK_BY_256  = _BV(CS02),
    CLK_BY_1024 = _BV(CS02) | _BV(CS00)
  } Clock;

  typedef enum { OVERFLOW, COMP_MATCH_A, COMP_MATCH_B } Interrupt;

  /*
   * Must define interrupt handler body before enabling:
   * TIMER0_OVF_vect, TIMER0_COMPA_vect, TIMER0_COMPB_vect
   */
  static UNUSED inline void enableInterrupt(Timer0::Interrupt interrupt) {
    switch (interrupt) {
      case OVERFLOW:     bset(TIMSK0, TOIE0); break;
      case COMP_MATCH_A: bset(TIMSK0, OCIE0A); break;
      case COMP_MATCH_B: bset(TIMSK0, OCIE0B); break;
    }
  }

  static UNUSED inline void disableInterrupt(Timer0::Interrupt interrupt) {
    switch (interrupt) {
      case OVERFLOW:     bclr(TIMSK0, TOIE0); break;
      case COMP_MATCH_A: bclr(TIMSK0, OCIE0A); break;
      case COMP_MATCH_B: bclr(TIMSK0, OCIE0B); break;
    }
  }

  static UNUSED inline void modeSelect(Mode mode, OutputA OA, OutputB OB) {
    if (OA)
      bset(DDRD, PD6);
    if (OB)
      bset(DDRD, PD5);
    TCCR0A = OA | OB | mode;
  }

  static UNUSED inline void clockSelect(Clock clock) {
    TCCR0B &= ~(_BV(CS02) | _BV(CS01) | _BV(CS00));
    TCCR0B |= clock;
  }

  static UNUSED inline void counter(uint8_t value) { TCNT0 = value; }
  static UNUSED inline void compareA(uint8_t value) { OCR0A = value; }
  static UNUSED inline void compareB(uint8_t value) { OCR0B = value; }
};

#endif
