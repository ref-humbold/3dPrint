#ifndef __laser_test_H
#define __laser_test_H

#include "devices.h"
#include "gpio.h"
#include "main.h"

void laser_test()
{
    HAL_Delay(15000);
    laser_on();
    builtin_led_on();

    HAL_Delay(30000);
    laser_off();
    builtin_led_off();
}

#endif
