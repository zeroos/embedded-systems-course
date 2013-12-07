#!/usr/bin/env python2.7

import math
import textwrap

sintab = [ int(math.sin(i * math.pi / 256) * 127 + 128) for i in range(-128, 128) ]

print "#include <avr/pgmspace.h>"
print ""
print "const uint8_t sintab[%d] PROGMEM = {" % len(sintab)
print textwrap.fill(", ".join(map(str, sintab)),
                    width=80, initial_indent="  ", subsequent_indent="  ")
print "};"
