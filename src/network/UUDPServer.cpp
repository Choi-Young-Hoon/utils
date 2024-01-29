#include "network/UUDPServer.hpp"

#include <iostream>

namespace utils {
	UUDPServer::UUDPServer(unsigned short port) {
		this->socket = std::make_unique<boost::asio::ip::udp::socket>(this->ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port));
	}

	UUDPServer::~UUDPServer() {
		//this->stop();
	}

	bool UUDPServer::asyncServiceRun() {
		this->ioService.run();

		return true;
	}

	void UUDPServer::asyncServiceStop() {
		this->closeSocket();
		this->ioService.stop();
	}	

	void UUDPServer::closeSocket() {
		this->socket->close();
	}

	size_t UUDPServer::recv(UByteBuffer* buffer, int recvBufferSize, UResult* result) {
		if (result == nullptr ||
			buffer == nullptr) {
			return -1;
		}
		buffer->resize(recvBufferSize);

		boost::system::error_code error;
		size_t size = this->socket->receive_from(boost::asio::buffer(*buffer), this->endpoint, 0, error);
		if (error) {
			return result->failedReturnValue(error.value(), error.message());
		}
	
		return result->successReturnValue(size);
	}

	size_t UUDPServer::send(const UByteBuffer& buffer, UResult* result) {
		if (result == nullptr) {
			return -1;
		}

		boost::system::error_code error;
		size_t size = this->socket->send_to(boost::asio::buffer(buffer), this->endpoint, 0, error);
		if (error) {
			return result->failedReturnValue(error.value(), error.message());
		}

		return result->successReturnValue(size);
	}

	void UUDPServer::asyncRecv(int recvBufferSize, UAsyncCallback callback) {
		this->recvBuffer.resize(recvBufferSize);

		this->socket->async_receive_from(boost::asio::buffer(this->recvBuffer), this->endpoint, 
			[=](boost::system::error_code ec, std::size_t bytesReceived) {
				if (!ec && bytesReceived > 0) {
					callback(this->recvBuffer, bytesReceived);
				}
			}
		);
	}

	void UUDPServer::asyncSend(const UByteBuffer& buffer) {
		this->socket->async_send_to(boost::asio::buffer(buffer), this->endpoint,
			[this](boost::system::error_code ec, std::size_t bytesSent) {
				if (!ec && bytesSent > 0) {

				}
			}
		);
	}
};