#include "commands.h"

send_to_dac(point * p)
{
    dac_write(&hspi2, &DacPinX, p->x);
    dac_write(&hspi2, &DacPinY, p->y);
}

move(point * p)
{
    laser_off(1);
    send_to_dac(p);
    laser_on(1);
}

linear(point * p)
{
    laser_on(1);
    send_to_dac(p);
}
