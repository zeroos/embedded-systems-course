#ifndef __RAWUNO_COMMON_H__
#define __RAWUNO_COMMON_H__

#include <stdint.h>
#include <avr/sfr_defs.h>

#define UNUSED __attribute__((unused))
#define PURE __attribute__((pure))

typedef volatile uint8_t *io_reg_t;

template <typename T>
void bclr(T &word, uint8_t pos) { word &= ~_BV(pos); }

template <typename T>
void bset(T &word, uint8_t pos) { word |= _BV(pos); }

template <typename T>
T bget(T word, uint8_t pos) { return (word & _BV(pos)); }

template <typename T0, typename T1>
void bput(T0 &word, uint8_t pos, T1 value)
{
  if (value) bset(word, pos); else bclr(word, pos);
}

#endif
