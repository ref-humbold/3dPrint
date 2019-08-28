#ifndef __controller_H
#define __controller_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "gpio.h"
#include "spi.h"

    extern uint8_t DacConfig;
    extern pinout LaserPin;
    extern pinout DacPinX;
    extern pinout DacPinY;

    /**
     * MCP 4921 Digital-Analog Converter
     * data [lower 12 bits of uint16_t]
     */
    void dac_write(SPI_HandleTypeDef * hspi, pinout * device, uint16_t data);

    void laser_on();

    void laser_off();

#ifdef __cplusplus
}
#endif
#endif
