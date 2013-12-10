#ifndef __RAWUNO_PROGMEM_H__
#define __RAWUNO_PROGMEM_H__

#include "Common.h"

#ifndef PROGMEM
#define PROGMEM __attribute__((progmem))
#endif

#define PGM_BYTE_ARRAY(NAME, ...) \
  const struct { \
    uint8_t operator[](uint16_t index) const { \
      static const uint8_t NAME ## _array [] PROGMEM = { __VA_ARGS__ }; \
      return pgm_read_byte_near((uint16_t)NAME ## _array + index); \
    } \
  } NAME;

#endif
