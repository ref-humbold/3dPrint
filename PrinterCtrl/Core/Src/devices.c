#include "commands.h"
#include "gpio.h"

const uint8_t DacConfig = 0x03;
const pinout LaserPin = {.gpio = GPIOB, .pin = GPIO_PIN_2};
const pinout DacPinX = {.gpio = GPIOC, .pin = GPIO_PIN_4};
const pinout DacPinY = {.gpio = GPIOC, .pin = GPIO_PIN_5};

void dac_write(SPI_HandleTypeDef * hspi, const pinout * device, uint16_t data)
{
    uint16_t data_dac = ((DacConfig & 0x0F) << 12) | (data & 0x0FFF);

    spi_send(hspi, device, data_dac);
}

void laser_on()
{
    HAL_GPIO_WritePin(LaserPin.gpio, LaserPin.pin, GPIO_PIN_RESET);
    HAL_Delay(1000);
}

void laser_off()
{
    HAL_GPIO_WritePin(LaserPin.gpio, LaserPin.pin, GPIO_PIN_SET);
    HAL_Delay(1000);
}
