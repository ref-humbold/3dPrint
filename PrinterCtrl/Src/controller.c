#include "controller.h"

void dac_write(SPI_HandleTypeDef * hspi, pinout * device, uint8_t config, uint16_t data)
{
    uint16_t data_dac = ((config & 0x0F) << 12) | (data & 0x0FFF);

    spi_send_16(hspi, device, data_dac);
}
