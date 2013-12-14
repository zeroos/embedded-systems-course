#!/usr/bin/env python2.7

import subprocess
import sys

RED = "\033[31;1m"
GRN = "\033[32;1m"
BLU = "\033[34;1m"
GRY = "\033[30;1m"
RST = "\033[0m"


def fit(cur, top):
  color = RED
  if cur <= top:
    color = GRN
  if cur == 0:
    color = GRY
  return "%s%d%s / %s%d%s" % (color, cur, RST, BLU, top, RST)


if __name__ == '__main__':
  output = subprocess.check_output(["avr-objdump", "-h", sys.argv[1]])
  lines = [line.strip() for line in output.split('\n')]
  sections = {}

  for line in lines:
    fields = line.split()
    if len(fields) == 7:
      name, size = fields[1:3]
      sections[name] = int(size, base=16)

  text = sections.get('.text', 0)
  data = sections.get('.data', 0)
  bss = sections.get('.bss', 0)
  noinit = sections.get('.noinit', 0)
  eeprom = sections.get('.eeprom', 0)

  print "RAM: {0}, EEPROM: {2}, FLASH: {1}".format(
    fit(data + bss + noinit, 2048), fit(text + data, 32768), fit(eeprom, 1024))
