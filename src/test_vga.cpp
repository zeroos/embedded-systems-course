#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/atomic.h>

#include "Pin.h"
#include "Timer0.h"

static Pin::Pin<8> hsync;
static Pin::Pin<9> vsync;
static Pin::Pin<13> led;

#define HSYNC_H PORTB |= 0b00000001
#define HSYNC_L PORTB &= 0b11111110

#define VSYNC_H PORTB |= 0b00000010 
#define VSYNC_L PORTB &= 0b11111101

#define LED_ON  PORTB |= 0b00100000
#define LED_OFF PORTB &= 0b11011111
#define TOGGLE_LED PORTB ^= 0b00100000


volatile char half_wall_height;
volatile int lines = 0;
volatile char line_state = 0;
volatile char wall_start = 20;
volatile char wall_end = 60;

volatile char wall_color = 0x0f;
volatile char ceiling_color = 0x00;

ISR(TIMER0_COMPA_vect) {
  HSYNC_L;
  lines++;
  switch(lines) {
    case 1:
      VSYNC_L;
      line_state = 3;
      break;
    case 3:
      VSYNC_H;
      line_state = 0;
      break;
    case 525:
      lines=0;
      break;
    default:
      wall_start = 37-half_wall_height;
      wall_end = 37+half_wall_height;
      break;
  }
}

ISR(TIMER0_COMPB_vect) {
  static char line_state=0;
  switch (line_state) {
    case 0:
      HSYNC_H;
      line_state = 1;
      OCR0B = wall_start;
      break;
    case 1:
      PORTD = wall_color;
      line_state = 2;
      OCR0B = wall_end;
      break;
    case 2:
      PORTD = ceiling_color;
      line_state = 0;
      OCR0B = 2;
      break;
    default:
      OCR0B = 2;
      HSYNC_H;
  }
}


inline int get_half_wall_height(int line_number) {
    return 3+line_number%19;
}

int main() {
  DDRD = 0xFF;
  PORTD = 0xFF;

  hsync.mode(OUTPUT);
  vsync.mode(OUTPUT);
  led.mode(OUTPUT);

  hsync.low();

  Timer0::modeSelect(Timer0::CTC, Timer0::SET_ON_MATCH_A, Timer0::DISABLE_B);
  Timer0::clockSelect(Timer0::CLK_BY_8);
  Timer0::enableInterrupt(Timer0::COMP_MATCH_A);
  Timer0::enableInterrupt(Timer0::COMP_MATCH_B);

  /* Set initial counter and compare values */
  Timer0::counter(0);
  Timer0::compareA(64);
  Timer0::compareB(11);

  sei();

  int prev_line = 0;
  while(true) {
    while(prev_line == lines);
    prev_line = lines;

    /*
     * Start of computations made before each line
     */

    if(lines < 200) {
        wall_color = 0b00001100;
    }else if(lines < 300) {
        wall_color = 0b00000011;
    }else if(lines < 400) {
        wall_color = 0b00110010;
    }else{
        wall_color = 0b00110000;
    }
    half_wall_height = 3+lines%18;

    /*
     * End of computations made before each line
     */


    if(lines < 5) {
      /*
       * Start of computations made before each frame
       */


      /*
       * End of computations made before each frame
       */
    }
  }
}
