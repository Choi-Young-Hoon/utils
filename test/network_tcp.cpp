#include "gtest/gtest.h"

#include "type/UResult.hpp"
#include "type/UByteBuffer.hpp"
#include "network/UTCPClient.hpp"
#include "network/UTCPServer.hpp"
#include "network/UTCPSession.hpp"

#include <memory>
#include <iostream>
#include <string>
#include <thread>

#define TEST_SERVER_PORT 12345

static std::string requestMessage  = "Hello World!";
static std::string responseMessage = "Hello World! Hello World! Hello World!";

class TCPTestServer : public ::testing::Test {
protected:
	void SetUp() override {
		this->server = std::make_unique<utils::UTCPServer>(TEST_SERVER_PORT);
		this->echoThread = std::make_unique<std::thread>([this]() {
			utils::UResult result;
			utils::UByteBuffer buffer;
			
			this->server->createAcceptor(&result);
			if (!result.isSucceed()) {
				std::cout << "Server Accept Failed: " << result.getErrorMessage() << std::endl;
				return;
			}

			utils::UTCPSessionPtr clientSession = this->server->accept(&result);
			if (result.isSucceed() == false) {
				std::cout << "Server Accept Failed: " << result.getErrorMessage() << std::endl;
				return;
			}
			std::cout << "Server Accept Success" << std::endl;

			std::cout << "Server Recv...." << std::endl;
			size_t recvSize = clientSession->recv(&buffer, 4096, &result);
			if (!result.isSucceed()) {
				std::cout << "Server Recv Failed: " << result.getErrorMessage() << std::endl;
				return;
			}
			std::cout << "Server Recv size: " << recvSize << " Data: " << std::string(buffer.begin(), buffer.end()) << std::endl;

			buffer.setText(responseMessage);
			size_t sendSize = clientSession->send(buffer, &result);
			if (!result.isSucceed()) {
				std::cout << "Sever Send Failed: " << result.getErrorMessage() << std::endl;
				return;
			}
			std::cout << "Server Send size: " << sendSize << " Data: " << responseMessage << std::endl;
		});
	}

	void TearDown() override {
		this->server->asyncServiceStop();
		this->echoThread->join();
	}

private:
	std::unique_ptr<utils::UTCPServer> server;
	std::unique_ptr<std::thread> echoThread;
};

TEST_F(TCPTestServer, TCP_SYNC_TEST) {
	utils::UResult result;
	utils::UTCPClient client("127.0.0.1", TEST_SERVER_PORT);
	bool isConnected = client.connect(&result);
	ASSERT_TRUE(result.isSucceed());
	ASSERT_TRUE(isConnected);

	std::cout << "Client Send...." << std::endl;
	size_t size = client.send(utils::UByteBuffer(requestMessage), &result);
	ASSERT_TRUE(result.isSucceed());
	ASSERT_EQ(size, requestMessage.length());
	std::cout << "Client Send size: " << size << " Data: " << requestMessage << std::endl;

	std::cout << "Client Recv...." << std::endl;
	utils::UByteBuffer buffer;
	size_t recvSize = client.recv(&buffer, 4096, &result);
	ASSERT_TRUE(result.isSucceed());
	ASSERT_EQ(recvSize, responseMessage.length());
	ASSERT_EQ(std::string(buffer.begin(), buffer.begin() + recvSize), responseMessage);

	std::cout << "Client Recv size: " << recvSize << " Data: " << std::string(buffer.begin(), buffer.end()) << std::endl;
}