#ifndef __messaging_H
#define __messaging_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "spi.h"
#include "usart.h"

    extern uint8_t * command;

    void start_messaging();
    size_t receive_command();

#ifdef __cplusplus
}
#endif
#endif
