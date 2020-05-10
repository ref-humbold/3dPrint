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

    extern point currentPoint;

    void move(point pt);
    void draw_line(point pt);

#ifdef __cplusplus
}
#endif
#endif
