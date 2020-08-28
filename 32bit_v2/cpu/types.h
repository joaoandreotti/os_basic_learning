#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

// this function will help to resolve addresses
#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

#endif
