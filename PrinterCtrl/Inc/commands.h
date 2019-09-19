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

    void send_to_dac(point * p);
    void move(point * p);
    void linear(point * p);

#ifdef __cplusplus
}
#endif
#endif
