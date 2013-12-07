#!/usr/bin/env python2.7

import subprocess
import sys

if __name__ == '__main__':
  output = subprocess.check_output(["avr-objdump", "-h", sys.argv[1]])
  lines = [line.strip() for line in output.split('\n')]
  sections = {}

  for line in lines:
    fields = line.split()
    if len(fields) == 7:
      name, size = fields[1:3]
      sections[name] = int(size, base=16)

  text = sections['.text']
  data = sections['.data']
  bss = sections['.bss']

  print "RAM: %d / 2048, FLASH: %d / 32768" % (data + bss, text + data)
