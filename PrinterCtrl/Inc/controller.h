#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include "gpio.h"
#include "spi.h"

    /**
     * MCP 4921 Digital-Analog Converter
     * config [4 bit]
     * data [12 bit]
     */
    void dac_write(SPI_HandleTypeDef * hspi, pinout * device, uint8_t config, uint16_t data);

#ifdef __cplusplus
}
#endif
#endif
