#ifndef __laser_test_H
#define __laser_test_H

#include "controller.h"
#include "gpio.h"
#include "main.h"

void laser_test()
{
    HAL_Delay(10000);
    laser_on(3);
    builtin_led_on();
    HAL_Delay(20000);
    laser_off(3);
    builtin_led_off();
}

#endif
