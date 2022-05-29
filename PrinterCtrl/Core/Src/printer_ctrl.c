#include "printer_ctrl.h"
#include "commands.h"
#include "devices.h"
#include "usart.h"

void run_init()
{
    laser_off();
    start_connection();
}

void run_loop()
{
    command cmd = read_command();
    execute(cmd);
    clear_command(&cmd);
}
