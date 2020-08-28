#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include "../drivers/screen.h"
#include "isr.h"

void init_timer(uint32_t freq);

#endif
