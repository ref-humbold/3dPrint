#ifndef __commands_H
#define __commands_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"
#include "spi.h"
#include "usart.h"

    extern command cmd;
    extern point currentPoint;
    extern const uint8_t DacConfig;
    extern const pinout LaserPin;
    extern const pinout DacPinX;
    extern const pinout DacPinY;

    command init_command(size_t size);
    void clear_command(command * cmd);
    command read_command();

    /**
     * MCP 4921 Digital-Analog Converter
     * data [lower 12 bits of uint16_t]
     */
    void dac_write(SPI_HandleTypeDef * hspi, const pinout * device, uint16_t data);
    void laser_on();
    void laser_off();

    void move(point pt);
    void draw(point pt);
    void execute(command cmd);

#ifdef __cplusplus
}
#endif
#endif
