#include "controller.h"

pinout laser_pin = {.gpio = GPIOB, .pin = GPIO_PIN_2};

void dac_write(SPI_HandleTypeDef * hspi, pinout * device, uint8_t config, uint16_t data)
{
    uint16_t data_dac = ((config & 0x0F) << 12) | (data & 0x0FFF);

    spi_send_16(hspi, device, data_dac);
}

void laser_on()
{
    HAL_GPIO_WritePin(laser_pin.gpio, laser_pin.pin, GPIO_PIN_SET);
}

void laser_off()
{
    HAL_GPIO_WritePin(laser_pin.gpio, laser_pin.pin, GPIO_PIN_RESET);
}
