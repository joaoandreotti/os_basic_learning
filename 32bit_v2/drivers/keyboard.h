#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include "ports.h"
#include "../cpu/isr.h"
#include "screen.h"

void init_keyboard ();
void print_letter (uint8_t scancode);

#endif
