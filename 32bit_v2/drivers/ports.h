#ifndef PORTS_H
#define PORTS_H

#include "../cpu/types.h"
#include <stdint.h>

uint8_t port_byte_in (uint16_t);
void port_byte_out (uint16_t, uint8_t);

uint16_t port_word_in (uint16_t);
void port_word_out (uint16_t, uint16_t);

uint32_t port_dword_in (uint16_t);
void port_dword_out (uint16_t, uint32_t);

#endif
