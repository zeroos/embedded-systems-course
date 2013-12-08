#ifndef __RAWUNO_COMMON_H__
#define __RAWUNO_COMMON_H__

#include <stdint.h>
#include <avr/sfr_defs.h>
#include <avr/pgmspace.h>

#define UNUSED __attribute__((unused))
#define PURE __attribute__((pure))

typedef volatile uint8_t *io_reg_t;

#define bit_set(port, bit, value) \
{ if (value) { port |= _BV(bit); } else { port &= ~_BV(bit); } }

#endif
