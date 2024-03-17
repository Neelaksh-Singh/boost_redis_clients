#include <iostream>
#include <sstream>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/use_future.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/algorithm/string.hpp>

using boost::asio::ip::tcp;

class NetworkInterface {
public:
    virtual ~NetworkInterface() {}
    virtual void write(const std::string& data) = 0;
    virtual std::string read() = 0;
};

class MockNetwork : public NetworkInterface {
public:
    MOCK_METHOD(void, write, (const std::string& data), (override));
    MOCK_METHOD(std::string, read, (), (override));
};

class Producer {
public:
    Producer(boost::asio::io_context& io_context, NetworkInterface& network)
        : socket_(io_context), network_(network) {}

    void sendData(const std::string& data) {
        // Format the command to push data to the Redis queue
        std::string command = "LPUSH my_queue " + data + "\r\n";
        network_.write(command);

        std::string reply = network_.read();
        boost::algorithm::trim(reply);
        std::cout << "Redis reply: " << reply << std::endl;
    }

private:
    tcp::socket socket_;
    NetworkInterface& network_;
};

// Test case for Producer
TEST(ProducerTest, SendDataTest) {
    boost::asio::io_context io_context;
    MockNetwork mockNetwork;

    // Set expectations
    std::string expectedCommand = "LPUSH my_queue test_data\r\n";
    EXPECT_CALL(mockNetwork, write(expectedCommand));

    // Simulate Redis reply
    EXPECT_CALL(mockNetwork, read())
        .WillOnce(testing::Return("OK"));

    // Instantiate Producer with mock network
    Producer producer(io_context, mockNetwork);

    // Test sending data
    producer.sendData("test_data");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
