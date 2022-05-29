#include <cstdlib>
#include <string>
#include <gtest/gtest.h>
#include "usart_ctrl.hpp"

std::string port;

TEST(UsartTest, connect)
{
    usart_ctrl usart(port);

    usart.send(Connect);
    usart.assert_receive(Connect);
};

TEST(UsartTest, sendAndReceiveData)
{
    usart_ctrl usart(port);
    uint16_t data = 0x1234;

    usart.send(BeginTransmit);
    usart.send(data);
    usart.send(EndTransmit);
    usart.assert_receive(0x1);
    usart.assert_receive(data);
    usart.assert_receive(Acknowledge);
};

TEST(UsartTest, sendDataExpected_WhenAcknowlegeExpected)
{
    usart_ctrl usart(port);

    usart.send(DataExpected);
    usart.assert_receive(Failure);
};

int main(int argc, char * argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    port = argv[1];
    return RUN_ALL_TESTS();
}
