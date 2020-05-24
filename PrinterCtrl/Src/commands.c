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
