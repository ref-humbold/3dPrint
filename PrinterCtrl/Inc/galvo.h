#ifndef GALVO_H_
#define GALVO_H_

#include <inttypes.h>
#include "spi.h"

extern GPIO_TypeDef * laser_IO;
extern uint16_t laser_pin;

void laser_on();
void laser_off();

#endif
