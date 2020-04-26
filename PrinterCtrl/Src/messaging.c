#include "messaging.h"

void start_messaging()
{
    uart_expect_receive(&huart2, Connect);
    uart_send(&huart2, Connect);
}

size_t receive_command()
{
    uint16_t size, data;
    size_t index = 0;

    uart_send(&huart2, DataExpected);
    uart_expect_receive(&huart2, BeginTransmit);
    uart_receive(&huart2, &size);

    command = malloc(size);

    do
    {
        uart_receive(&huart2, &data);

        if(data != EndTransmit)
        {
            command[index] = data;
            ++index;
        }
    } while(data != EndTransmit || index >= size);

    uart_send(&huart2, index);

    if(index == size)
        uart_send(&huart2, Acknowledge);
    else
        uart_send(&huart2, Failure);

    return index;
}
