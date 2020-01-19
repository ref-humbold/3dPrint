#ifndef __controller_H
#define __controller_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "gpio.h"
#include "spi.h"

    extern const uint8_t DacConfig;
    extern const pinout LaserPin;
    extern const pinout DacPinX;
    extern const pinout DacPinY;

    /**
     * MCP 4921 Digital-Analog Converter
     * data [lower 12 bits of uint16_t]
     */
    void dac_write(SPI_HandleTypeDef * hspi, const pinout * device, uint16_t data);

    void laser_on();

    void laser_off();

#ifdef __cplusplus
}
#endif
#endif
