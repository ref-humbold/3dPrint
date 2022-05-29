#ifndef ___dac_test_H
#define ___dac_test_H

#include "devices.h"
#include "gpio.h"
#include "main.h"
#include "usart.h"

void dac_test()
{
    laser_on();
    HAL_Delay(5000);

    builtin_led_on();
    dac_write(&hspi2, &DacPinX, 0x0000);
    dac_write(&hspi2, &DacPinY, 0x0000);
    usart_send(&huart2, '0');
    usart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_off();
    dac_write(&hspi2, &DacPinX, 0x0100);
    dac_write(&hspi2, &DacPinY, 0x0100);
    usart_send(&huart2, '1');
    usart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_on();
    dac_write(&hspi2, &DacPinX, 0x0200);
    dac_write(&hspi2, &DacPinY, 0x0200);
    usart_send(&huart2, '2');
    usart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_off();
    dac_write(&hspi2, &DacPinX, 0x0300);
    dac_write(&hspi2, &DacPinY, 0x0300);
    usart_send(&huart2, '3');
    usart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_on();
    dac_write(&hspi2, &DacPinX, 0x0400);
    dac_write(&hspi2, &DacPinY, 0x0400);
    usart_send(&huart2, '4');
    usart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_off();
    dac_write(&hspi2, &DacPinX, 0x0500);
    dac_write(&hspi2, &DacPinY, 0x0500);
    usart_send(&huart2, '5');
    usart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_on();
    dac_write(&hspi2, &DacPinX, 0x0600);
    dac_write(&hspi2, &DacPinY, 0x0600);
    usart_send(&huart2, '6');
    usart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_off();
    dac_write(&hspi2, &DacPinX, 0x0700);
    dac_write(&hspi2, &DacPinY, 0x0700);
    usart_send(&huart2, '7');
    usart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_on();
    dac_write(&hspi2, &DacPinX, 0x0800);
    dac_write(&hspi2, &DacPinY, 0x0800);
    usart_send(&huart2, '8');
    usart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_off();
    dac_write(&hspi2, &DacPinX, 0x0C00);
    dac_write(&hspi2, &DacPinY, 0x0C00);
    usart_send(&huart2, 'C');
    usart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_on();
    dac_write(&hspi2, &DacPinX, 0x0FFF);
    dac_write(&hspi2, &DacPinY, 0x0FFF);
    usart_send(&huart2, 'F');
    usart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_off();
    usart_send(&huart2, '\r');
    usart_send(&huart2, '\n');

    laser_off();
    HAL_Delay(10000);
}

#endif
