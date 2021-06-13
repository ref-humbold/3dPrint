#include "commands.h"
#include "gpio.h"

point currentPoint = {.x = 0, .y = 0};
const uint8_t DacConfig = 0x03;
const pinout LaserPin = {.gpio = GPIOB, .pin = GPIO_PIN_2};
const pinout DacPinX = {.gpio = GPIOC, .pin = GPIO_PIN_4};
const pinout DacPinY = {.gpio = GPIOC, .pin = GPIO_PIN_5};

command init_command(size_t size)
{
    command cmd;

    cmd.cmd = malloc(size);
    cmd.size = size;
    return cmd;
}

void clear_command(command * cmd)
{
    if(cmd->cmd != NULL)
    {
        free(cmd->cmd);
        cmd->size = 0;
    }
}

command read_command()
{
    uint16_t size, data;
    size_t index = 0;

    uart_send(&huart2, DataExpected);
    uart_expect_receive(&huart2, BeginTransmit);
    uart_receive(&huart2, &size);

    command cmd = init_command(size);

    do
    {
        uart_receive(&huart2, &data);

        if(data != EndTransmit)
        {
            cmd.cmd[index] = data;
            ++index;
        }
    } while(data != EndTransmit || index >= size);

    uart_send(&huart2, index);

    if(index == size)
        uart_send(&huart2, Acknowledge);
    else
        uart_send(&huart2, Failure);

    return cmd;
}

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

void send_to_dac(point pt)
{
    dac_write(&hspi2, &DacPinX, pt.x);
    dac_write(&hspi2, &DacPinY, pt.y);
}

void move(point pt)
{
    laser_off();
    send_to_dac(pt);
    laser_on();
    currentPoint = pt;
    HAL_Delay(200);
}

void draw(point pt)
{
    laser_on();
    send_to_dac(pt);
    currentPoint = pt;
    HAL_Delay(200);
}

void execute(command cmd)
{
    size_t i;
    int g = -1;
    point pt = {.x = 0, .y = 0};

    for(i = 0; i < cmd.size; i += 2)
    {
        switch(cmd.cmd[i])
        {
            case 'G':
                g = cmd.cmd[i + 1];
                break;

            case 'X':
                pt.x = cmd.cmd[i + 1];
                break;

            case 'Y':
                pt.y = cmd.cmd[i + 1];
                break;

            default:
                break;
        }
    }

    switch(g)
    {
        case 0:
            move(pt);
            break;

        case 1:
            draw(pt);
            break;

        default:
            break;
    }
}
