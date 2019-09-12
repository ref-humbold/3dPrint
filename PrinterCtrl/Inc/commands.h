#ifndef __commands_H
#define __commands_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "controller.h"
#include "spi.h"

    typedef struct
    {
        uint8_t x;
        uint8_t y;
    } point;

    send_to_dac(point * p);
    move(point * p);
    linear(point * p);

#ifdef __cplusplus
}
#endif
#endif
