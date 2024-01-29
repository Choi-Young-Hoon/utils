#include "gtest/gtest.h"

#include "type/UResult.hpp"
#include "type/UByteBuffer.hpp"

#include "network/UUDPServer.hpp"
#include "network/UUDPClient.hpp"

#include <iostream>
#include <thread>
#include <vector>
#include <string>

#define TEST_ASYNC_SERVER_PORT 12345
#define TEST_SYNC_SERVER_PORT  12346

#define TEST_BUFFER_SIZE 4096

static std::string requestMessage  = "Hello World!";
static std::string responseMessage = "Hello World! Hello World! Hello World!";

class UDPTestAsyncServer : public ::testing::Test {
protected:
	void SetUp() override {
		this->server = std::make_unique<utils::UUDPServer>(TEST_ASYNC_SERVER_PORT);

		this->serverThread = std::make_unique<std::thread>([this]() {
			this->server->asyncRecv(TEST_BUFFER_SIZE,
				[&](utils::UByteBuffer& buffer, size_t recvSize) {
					std::cout << "Server Recv size: " << recvSize << " Data: " << std::string(buffer.begin(), buffer.end()) << std::endl;
					buffer.setText(responseMessage);
					this->server->asyncSend(buffer);
				});
			this->server->asyncServiceRun();
		});
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "Server Start...." << std::endl;
	}

	void TearDown() override {
		this->server->asyncServiceStop();
		this->serverThread->join();
	}

private:
	std::unique_ptr<std::thread> serverThread;
	std::unique_ptr<utils::UUDPServer> server;
};

class UDPTestServer : public ::testing::Test {
protected:
	void SetUp() override {
		this->server = std::make_unique<utils::UUDPServer>(TEST_SYNC_SERVER_PORT);
		this->echoThread = std::make_unique<std::thread>([this]() {
			utils::UResult result;
			utils::UByteBuffer buffer;
			size_t recvSize = this->server->recv(&buffer, 1024, &result);
			std::cout << "Server Recv size: " << recvSize << " Data: " << std::string(buffer.begin(), buffer.end()) << std::endl;

			buffer.setText(responseMessage);
			this->server->send(buffer, &result);
		});
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	void TearDown() override {
		this->server->closeSocket();
		this->echoThread->join();
	}

private:
	std::unique_ptr<std::thread> echoThread;
	std::unique_ptr<utils::UUDPServer> server;
};

TEST_F(UDPTestAsyncServer, UDP_ASYNC_TEST) {
	utils::UResult result;

	utils::UUDPClient client("127.0.0.1", TEST_ASYNC_SERVER_PORT);

	utils::UByteBuffer buffer(requestMessage);

	std::cout << "Client Send...." << std::endl;
	client.asyncSend(buffer);
	client.asyncRecv(1024, [&](utils::UByteBuffer& responseBuffer, size_t recvSize) {
		std::cout << "Client Recv size: " << recvSize << " Data: " << std::string(responseBuffer.begin(), responseBuffer.end()) << std::endl;
		ASSERT_EQ(std::string(responseBuffer.begin(), responseBuffer.end()), responseMessage);
		ASSERT_EQ(responseBuffer.size(), responseMessage.size());
	});

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

TEST_F(UDPTestServer, UDP_SYNC_TEST) {
	utils::UResult result;

	utils::UUDPClient client("127.0.0.1", TEST_SYNC_SERVER_PORT);


	////////////////////////////////////////// send to server
	utils::UByteBuffer buffer(requestMessage);
	std::cout << "Client Send...." << std::endl;
	size_t size = client.send(buffer, &result);
	ASSERT_EQ(size, requestMessage.length());
	ASSERT_TRUE(result.isSucceed());

	//////////////////////////////////////////// recv from server
	std::cout << "Client Recv...." << std::endl;
	size = client.recv(&buffer, TEST_BUFFER_SIZE, &result);
	std::cout << "Client Recv size: " << size << " Data: " << std::string(buffer.begin(), buffer.end()) << std::endl;
	ASSERT_EQ(size, responseMessage.size());
	ASSERT_EQ(std::string(buffer.begin(), buffer.begin() + size), responseMessage);
	ASSERT_TRUE(result.isSucceed());
}

TEST(UDP_NULL_TEST, UDP_NULL_TEST) {
	utils::UResult result;
	utils::UByteBuffer buffer;

	utils::UUDPServer server(0);
	ASSERT_EQ(server.send(buffer, nullptr), -1);
	ASSERT_EQ(server.recv(&buffer, TEST_BUFFER_SIZE, nullptr), -1);
	ASSERT_EQ(server.recv(nullptr, TEST_BUFFER_SIZE, &result), -1);

	utils::UUDPClient client("127.0.0.1", 0);
	ASSERT_EQ(client.send(buffer, nullptr), -1);
	ASSERT_EQ(client.recv(&buffer, TEST_BUFFER_SIZE, nullptr), -1);
	ASSERT_EQ(client.recv(nullptr, TEST_BUFFER_SIZE, &result), -1);
}