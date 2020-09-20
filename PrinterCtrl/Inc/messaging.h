#ifndef __messaging_H
#define __messaging_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "usart.h"

    extern command cmd;

    void clear_command(command * cmd);
    command init_command(size_t size);
    void start_messaging();
    command receive_command();

#ifdef __cplusplus
}
#endif
#endif
