#include "gtest/gtest.h"

#include "type/ByteBuffer.hpp"
#include "network/UUDPServer.hpp"
#include "network/UUDPClient.hpp"

#include <iostream>
#include <thread>
#include <vector>
#include <string>

#define TEST_SERVER_PORT 12345

class UDPTestAsyncServer : public ::testing::Test {
public:
	virtual ~UDPTestAsyncServer() {
		this->serverThread.join();
		this->echoThread.join();
	}
protected:
	void SetUp() override {
		this->server = std::make_unique<utils::UUDPServer>(TEST_SERVER_PORT);
		this->serverThread = std::thread([&]() {
			std::cout << "Server Start..." << std::endl;
			this->server->start();
		});
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		this->echoThread = std::thread([&]() {
			while (this->isRunning) {
				utils::ByteBuffer buffer;
				int size = this->server->recv(&buffer);
				if (size > 0) {
					std::cout << "Server recv: " << std::string(buffer.begin(), buffer.end()) << " Size: " << size << std::endl;
					//this->server->send(buffer);
					this->server->asyncSend(buffer);
				} else {

				}
			}
			std::cout << "stop..." << std::endl;
		});
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	void TearDown() override {
		this->server->stop();
		this->isRunning = false;
	}

private:
	bool isRunning = true;
	std::thread serverThread;
	std::thread echoThread;

	std::unique_ptr<utils::UUDPServer> server;
};

TEST_F(UDPTestAsyncServer, UDP_SYNC_TEST) {
	utils::UUDPClient client("127.0.0.1", TEST_SERVER_PORT);

	std::string message = "Hello World!";
	utils::ByteBuffer buffer(message);
	std::cout << "Client Send...." << std::endl;
	int size = client.send(buffer);
	ASSERT_EQ(size, message.size());

	buffer.clear();
	std::cout << "Client Recv...." << std::endl;
	size = client.recv(&buffer);
	std::cout << "Client Recv size: " << buffer.size() << std::endl;
	ASSERT_EQ(size, message.size());
	ASSERT_EQ(std::string(buffer.begin(), buffer.end()), message);
}

TEST_F(UDPTestAsyncServer, UDP_ASYNC_TEST) {
	utils::UUDPClient client("127.0.0.1", TEST_SERVER_PORT);

	std::string message = "Hello World!";

	client.asyncSend(utils::ByteBuffer(message));

	client.asyncRecv([&](utils::ByteBuffer& buffer) {
		std::cout << "Client Recv size: " << buffer.size() << std::endl;
		ASSERT_EQ(std::string(buffer.begin(), buffer.end()), message);
	});
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}