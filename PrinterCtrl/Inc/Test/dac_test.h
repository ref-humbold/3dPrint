#ifndef ___dac_test_H
#define ___dac_test_H

#include "controller.h"
#include "gpio.h"
#include "main.h"

void dac_test()
{
    dac_write(&hspi2, &DacPinX, 0x0000);
    dac_write(&hspi2, &DacPinY, 0x0000);
    HAL_Delay(5000);
    dac_write(&hspi2, &DacPinX, 0x0100);
    dac_write(&hspi2, &DacPinY, 0x0100);
    HAL_Delay(5000);
    dac_write(&hspi2, &DacPinX, 0x0200);
    dac_write(&hspi2, &DacPinY, 0x0200);
    HAL_Delay(5000);
    dac_write(&hspi2, &DacPinX, 0x0300);
    dac_write(&hspi2, &DacPinY, 0x0300);
    HAL_Delay(5000);
    dac_write(&hspi2, &DacPinX, 0x0400);
    dac_write(&hspi2, &DacPinY, 0x0400);
    HAL_Delay(5000);
    dac_write(&hspi2, &DacPinX, 0x0500);
    dac_write(&hspi2, &DacPinY, 0x0500);
    HAL_Delay(5000);
    dac_write(&hspi2, &DacPinX, 0x0600);
    dac_write(&hspi2, &DacPinY, 0x0600);
    HAL_Delay(5000);
}

#endif
