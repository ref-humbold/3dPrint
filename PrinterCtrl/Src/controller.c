#include "controller.h"

uint8_t DacConfig = 0x03;
pinout LaserPin = {.gpio = GPIOB, .pin = GPIO_PIN_2};
pinout DacPinX = {.gpio = GPIOC, .pin = GPIO_PIN_4};
pinout DacPinY = {.gpio = GPIOC, .pin = GPIO_PIN_5};

void dac_write(SPI_HandleTypeDef * hspi, pinout * device, uint16_t data)
{
    uint16_t data_dac = ((DacConfig & 0x0F) << 12) | (data & 0x0FFF);

    spi_send(hspi, device, data_dac);
}

void laser_on(uint8_t delay)
{
    HAL_GPIO_WritePin(LaserPin.gpio, LaserPin.pin, GPIO_PIN_RESET);
    HAL_Delay(delay * 1000);
}

void laser_off(uint8_t delay)
{
    HAL_GPIO_WritePin(LaserPin.gpio, LaserPin.pin, GPIO_PIN_SET);
    HAL_Delay(delay * 1000);
}
