#include "network/UTCPClient.hpp"

#include <iostream>

namespace utils {
	UTCPClient::UTCPClient(std::string& serverIpAddress, unsigned short port) {
		this->serverIpAddress =serverIpAddress;
		this->port			  = port;
	}

	UTCPClient::UTCPClient(std::string&& serverIpAddress, unsigned short port) {
		this->serverIpAddress = serverIpAddress;
		this->port			  = port;
	}

	UTCPClient::~UTCPClient() {
		this->close();
	}

	bool UTCPClient::connect(UResult* result) {
		if (result == nullptr) {
			return false;
		}

		boost::asio::ip::tcp::resolver resolver(this->ioContext);
		auto endpoints = resolver.resolve(this->serverIpAddress, std::to_string(this->port));
		this->socket   = std::make_shared<boost::asio::ip::tcp::socket>(this->ioContext);

		boost::system::error_code error;
		this->endpoint = boost::asio::connect(*this->socket, endpoints, error);
		if (error) {
			return result->failed(error.value(), error.message());
		}

		return result->success();
	}

	void UTCPClient::close() {
		if (this->socket != nullptr) {
			this->socket->close();
		}
	}

	size_t UTCPClient::recvUntil(UByteBuffer* buffer, const std::string& until, UResult* result) {
		if (result == nullptr ||
			buffer == nullptr) {
			return -1;
		}

		boost::system::error_code error;
		size_t size = boost::asio::read_until(*this->socket, boost::asio::dynamic_buffer(*buffer), until, error);
		if (error) {
			return result->failedReturnValue(error.value(), error.message());
		}

		return result->successReturnValue(size);
	}

	size_t UTCPClient::recv(UByteBuffer* buffer, int recvBufferSize, UResult* result) {
		if (result == nullptr ||
			buffer == nullptr) {
			return -1;
		}
		buffer->resize(recvBufferSize);

		boost::system::error_code error;
		size_t size = this->socket->read_some(boost::asio::buffer(*buffer), error);
		if (error) {
			std::cout << "UTCPClient::recv error: " << error.message() << std::endl;
			return result->failedReturnValue(error.value(), error.message());
		}

		return result->successReturnValue(size);
	}

	size_t UTCPClient::send(const UByteBuffer& buffer, UResult* result) {
		if (result == nullptr) {
			return -1;
		}

		boost::system::error_code error;
		size_t size = boost::asio::write(*this->socket, boost::asio::buffer(buffer), error);
		if (error) {
			return result->failedReturnValue(error.value(), error.message());	
		}

		return result->successReturnValue(size);
	}

	void UTCPClient::asyncRecv(int recvBufferSize, UAsyncCallback callback) {
		this->recvBuffer.resize(recvBufferSize);
		boost::asio::async_read(*this->socket, boost::asio::buffer(this->recvBuffer), boost::asio::transfer_exactly(recvBufferSize),
			[this, callback](boost::system::error_code ec, std::size_t bytesReceived) {
				if (!ec && bytesReceived > 0) {
					callback(this->recvBuffer, bytesReceived);
				}
			});
	}

	void UTCPClient::asyncSend(const UByteBuffer& buffer) {
		boost::asio::async_write(*this->socket, boost::asio::buffer(buffer),
			[this](boost::system::error_code ec, std::size_t bytesSent) {
				if (!ec && bytesSent > 0) {
					
				}
			});
	}
};