#include "commands.h"

point currentPoint = {.x = 0, .y = 0};

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

void run(command cmd)
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
