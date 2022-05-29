#ifndef ___dac_test_H
#define ___dac_test_H

#include "commands.h"
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
    uart_send(&huart2, '0');
    uart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_off();
    dac_write(&hspi2, &DacPinX, 0x0100);
    dac_write(&hspi2, &DacPinY, 0x0100);
    uart_send(&huart2, '1');
    uart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_on();
    dac_write(&hspi2, &DacPinX, 0x0200);
    dac_write(&hspi2, &DacPinY, 0x0200);
    uart_send(&huart2, '2');
    uart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_off();
    dac_write(&hspi2, &DacPinX, 0x0300);
    dac_write(&hspi2, &DacPinY, 0x0300);
    uart_send(&huart2, '3');
    uart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_on();
    dac_write(&hspi2, &DacPinX, 0x0400);
    dac_write(&hspi2, &DacPinY, 0x0400);
    uart_send(&huart2, '4');
    uart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_off();
    dac_write(&hspi2, &DacPinX, 0x0500);
    dac_write(&hspi2, &DacPinY, 0x0500);
    uart_send(&huart2, '5');
    uart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_on();
    dac_write(&hspi2, &DacPinX, 0x0600);
    dac_write(&hspi2, &DacPinY, 0x0600);
    uart_send(&huart2, '6');
    uart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_off();
    dac_write(&hspi2, &DacPinX, 0x0700);
    dac_write(&hspi2, &DacPinY, 0x0700);
    uart_send(&huart2, '7');
    uart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_on();
    dac_write(&hspi2, &DacPinX, 0x0800);
    dac_write(&hspi2, &DacPinY, 0x0800);
    uart_send(&huart2, '8');
    uart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_off();
    dac_write(&hspi2, &DacPinX, 0x0C00);
    dac_write(&hspi2, &DacPinY, 0x0C00);
    uart_send(&huart2, 'C');
    uart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_on();
    dac_write(&hspi2, &DacPinX, 0x0FFF);
    dac_write(&hspi2, &DacPinY, 0x0FFF);
    uart_send(&huart2, 'F');
    uart_send(&huart2, ' ');
    HAL_Delay(10000);
    builtin_led_off();
    uart_send(&huart2, '\r');
    uart_send(&huart2, '\n');

    laser_off();
    HAL_Delay(10000);
}

#endif
