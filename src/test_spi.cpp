#include <avr/sleep.h>
#include <stdio.h>

#include "ProgMem.h"
#include "Serial.h"
#include "SPI.h"

#define RFM73D_ACTIVATE 0b01010000
#define RFM73D_R_REGISTER(n) (n)
#define RFM73D_W_REGISTER(n) (n | 0b00100000)

int main() {
  Serial::init(38400);
  Serial::attachStdIO();

  SPI::init();
  SPI::transmit(RFM73D_ACTIVATE);
  SPI::transmit(0x53);

  puts_P(PSTR("written activate command"));

  uint8_t r7 = SPI::transmit(RFM73D_R_REGISTER(7));

  printf_P(PSTR("r7 = %x"), r7);

  while (true)
    sleep_mode();

  return 0;
}
