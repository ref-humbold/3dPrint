#ifndef ___dac_test_H
#define ___dac_test_H

#include "controller.h"
#include "gpio.h"
#include "main.h"

void dac_test()
{
    HAL_Delay(10000);
    builtin_led_on();
    laser_on(3);

    HAL_Delay(5000);
    dac_write(&hspi2, &DacPinX, 0x03C0);
    dac_write(&hspi2, &DacPinY, 0x03C0);
    HAL_Delay(30000);
    dac_write(&hspi2, &DacPinX, 0x0500);
    dac_write(&hspi2, &DacPinY, 0x0500);
    HAL_Delay(30000);

    builtin_led_off();
    laser_off(3);
}

#endif
