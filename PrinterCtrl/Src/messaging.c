#include "messaging.h"
#include "usart.h"

void clear_command(command * cmd)
{
    if(cmd->cmd != NULL)
    {
        free(cmd->cmd);
        cmd->size = 0;
    }
}

command init_command(size_t size)
{
    command cmd;

    cmd.cmd = malloc(size);
    cmd.size = size;
    return cmd;
}

void start_messaging()
{
    uart_expect_receive(&huart2, Connect);
    uart_send(&huart2, Connect);
}

command receive_command()
{
    uint16_t size, data;
    size_t index = 0;

    uart_send(&huart2, DataExpected);
    uart_expect_receive(&huart2, BeginTransmit);
    uart_receive(&huart2, &size);

    command cmd = init_command(size);

    do
    {
        uart_receive(&huart2, &data);

        if(data != EndTransmit)
        {
            cmd.cmd[index] = data;
            ++index;
        }
    } while(data != EndTransmit || index >= size);

    uart_send(&huart2, index);

    if(index == size)
        uart_send(&huart2, Acknowledge);
    else
        uart_send(&huart2, Failure);

    return cmd;
}
