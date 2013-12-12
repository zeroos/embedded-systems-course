#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdio.h>

#include "ProgMem.h"
#include "Serial.h"
#include "SPI.h"

/* This test is implemented for nRF24L01+ board. */

static Pin::Pin<SS> slaveSelect;

static void printRegister(uint8_t i) {
  printf_P(PSTR("READ REG[%d]: "), i);

  /* Each command is enveloped by SS going low */
  slaveSelect.low();
  printf_P(PSTR("%.2x "), SPI::transmit(i));
  printf_P(PSTR("%.2x\n"), SPI::transmit(0));
  slaveSelect.high();
}

int main() {
  Serial::init(38400);
  Serial::attachStdIO();
  SPI::init(SPI::MASTER, SPI::CLK_DIV16);

  sei();

  printf_P(PSTR("SEND ACTIVATE: "));
  slaveSelect.low();
  printf_P(PSTR("%.2x "), SPI::transmit(0b01010000));
  printf_P(PSTR("%.2x\n"), SPI::transmit(0x73));
  slaveSelect.high();

  for (int i = 0; i < 10; i++)
    printRegister(i);

  while (true)
    sleep_mode();

  return 0;
}
