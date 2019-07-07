#include "controller.h"

uint8_t DacConfig = 0x03;
pinout LaserPin = {.gpio = GPIOB, .pin = GPIO_PIN_2};

void dac_write(SPI_HandleTypeDef * hspi, pinout * device, uint16_t data)
{
    uint16_t data_dac = ((DacConfig & 0x0F) << 12) | (data & 0x0FFF);

    spi_send(hspi, device, data_dac);
}

void laser_on()
{
    HAL_GPIO_WritePin(LaserPin.gpio, LaserPin.pin, GPIO_PIN_SET);
}

void laser_off()
{
    HAL_GPIO_WritePin(LaserPin.gpio, LaserPin.pin, GPIO_PIN_RESET);
}
