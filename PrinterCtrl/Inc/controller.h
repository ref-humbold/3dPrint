#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include "gpio.h"
#include "spi.h"

    extern pinout laser_pin;

    /**
     * MCP 4921 Digital-Analog Converter
     * config [lower 4 bits of uint8_t]
     * data [lower 12 bits of uint8_t]
     */
    void dac_write(SPI_HandleTypeDef * hspi, pinout * device, uint8_t config, uint16_t data);

    void laser_on();
    void laser_off();

#ifdef __cplusplus
}
#endif
#endif
