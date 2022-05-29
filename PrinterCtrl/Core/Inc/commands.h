#ifndef __commands_H
#define __commands_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"
#include "spi.h"

    extern command cmd;
    extern point currentPoint;

    command init_command(size_t size);
    void clear_command(command * cmd);
    command read_command();

    void move(point pt);
    void draw(point pt);
    void execute(command cmd);

#ifdef __cplusplus
}
#endif
#endif
