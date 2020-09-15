#ifndef __commands_H
#define __commands_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "controller.h"
#include "spi.h"

    extern point currentPoint;

    void move(point pt);
    void draw(point pt);
    void run(command cmd);

#ifdef __cplusplus
}
#endif
#endif
