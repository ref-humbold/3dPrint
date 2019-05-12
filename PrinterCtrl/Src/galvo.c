#include "galvo.h"

GPIO_TypeDef * laser_IO = GPIOA;
uint16_t laser_pin = GPIO_PIN_8;

void laser_on()
{
    HAL_GPIO_WritePin(laser_IO, laser_pin, GPIO_PIN_SET);
}

void laser_off()
{
    HAL_GPIO_WritePin(laser_IO, laser_pin, GPIO_PIN_RESET);
}
