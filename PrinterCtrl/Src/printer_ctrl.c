#include "printer_ctrl.h"

void run_init()
{
    start_messaging();
}

void run_loop()
{
    command cmd = receive_command();
    execute(cmd);
    clear_command(&cmd);
}
