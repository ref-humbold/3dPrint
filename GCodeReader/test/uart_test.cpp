#include <cstdlib>
#include <string>
#include <gtest/gtest.h>
#include "uart_ctrl.hpp"

std::string port;

TEST(UartTest, connect)
{
    uart_ctrl uart(port);

    uart.send(Connect);
    uart.assert_receive(Connect);
};

TEST(UartTest, sendAndReceiveData)
{
    uart_ctrl uart(port);
    uint16_t data = 0x1234;

    uart.send(BeginTransmit);
    uart.send(data);
    uart.send(EndTransmit);
    uart.assert_receive(0x1);
    uart.assert_receive(data);
    uart.assert_receive(Acknowledge);
};

TEST(UartTest, sendDataExpected_WhenAcknowlegeExpected)
{
    uart_ctrl uart(port);

    uart.send(DataExpected);
    uart.assert_receive(Failure);
};

int main(int argc, char * argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    port = argv[1];
    return RUN_ALL_TESTS();
}
