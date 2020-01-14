#include "commands.h"

void send_to_dac(point * p)
{
    dac_write(&hspi2, &DacPinX, p->x);
    dac_write(&hspi2, &DacPinY, p->y);
}

void move(point * p)
{
    laser_off();
    send_to_dac(p);
    laser_on();
}

void linear(point * p)
{
    laser_on();
    send_to_dac(p);
}
