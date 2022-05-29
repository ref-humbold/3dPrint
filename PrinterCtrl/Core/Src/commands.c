#include "commands.h"
#include "devices.h"
#include "gpio.h"
#include "usart.h"

point currentPoint = {.x = 0, .y = 0};

command init_command(size_t size)
{
    command cmd;

    cmd.cmd = malloc(size);
    cmd.size = size;
    return cmd;
}

void clear_command(command * cmd)
{
    if(cmd->cmd != NULL)
    {
        free(cmd->cmd);
        cmd->size = 0;
    }
}

command read_command()
{
    uint16_t size, data;
    size_t index = 0;

    usart_send(&huart2, DataExpected);
    usart_expect_receive(&huart2, BeginTransmit);
    usart_receive(&huart2, &size);

    command cmd = init_command(size);

    do
    {
        usart_receive(&huart2, &data);

        if(data != EndTransmit)
        {
            cmd.cmd[index] = data;
            ++index;
        }
    } while(data != EndTransmit || index >= size);

    usart_send(&huart2, index);

    if(index == size)
        usart_send(&huart2, Acknowledge);
    else
        usart_send(&huart2, Failure);

    return cmd;
}

void send_to_dac(point pt)
{
    dac_write(&hspi2, &DacPinX, pt.x);
    dac_write(&hspi2, &DacPinY, pt.y);
}

void move(point pt)
{
    laser_off();
    send_to_dac(pt);
    laser_on();
    currentPoint = pt;
    HAL_Delay(200);
}

void draw(point pt)
{
    laser_on();
    send_to_dac(pt);
    currentPoint = pt;
    HAL_Delay(200);
}

void execute(command cmd)
{
    size_t i;
    int g = -1;
    point pt = {.x = 0, .y = 0};

    for(i = 0; i < cmd.size; i += 2)
    {
        switch(cmd.cmd[i])
        {
            case 'G':
                g = cmd.cmd[i + 1];
                break;

            case 'X':
                pt.x = cmd.cmd[i + 1];
                break;

            case 'Y':
                pt.y = cmd.cmd[i + 1];
                break;

            default:
                break;
        }
    }

    switch(g)
    {
        case 0:
            move(pt);
            break;

        case 1:
            draw(pt);
            break;

        default:
            break;
    }
}
