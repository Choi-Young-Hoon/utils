#include "network/UTCPSession.hpp"

#include <iostream>

namespace utils {
	UTCPSession::UTCPSession(boost::asio::ip::tcp::socket socket)
	: socket(std::move(socket))
	{

	}

	UTCPSession::~UTCPSession() {

	}

	std::shared_ptr<UTCPSession> UTCPSession::createSession(boost::asio::ip::tcp::socket socket) {
		return std::make_shared<UTCPSession>(std::move(socket));
	}

	void UTCPSession::closeSocket() {
		this->socket.close();
	}

	size_t UTCPSession::recv(UByteBuffer* buffer, int recvBufferSize, UResult* result) {
		if (result == nullptr ||
			buffer == nullptr) {
			return -1;
		}
		buffer->resize(recvBufferSize);

		boost::system::error_code error;
		size_t size = this->socket.read_some(boost::asio::buffer(*buffer), error);
		if (error) {
			return result->failedReturnValue(error.value(), error.message());
		}

		return result->successReturnValue(size);
	}

	size_t UTCPSession::send(const UByteBuffer& buffer, UResult* result) {
		if (result == nullptr) {
			return -1;
		}

		boost::system::error_code error;
		size_t size = this->socket.write_some(boost::asio::buffer(buffer), error);
		if (error) {
			return result->failedReturnValue(error.value(), error.message());
		}

		return result->successReturnValue(size);
	}

	void UTCPSession::asyncSend(const UByteBuffer& buffer) {
		this->socket.async_read_some(boost::asio::buffer(this->recvBuffer),
			[this](boost::system::error_code ec, std::size_t bytesSent) {
				if (!ec && bytesSent > 0) {
					
				}
			});
	}

	void UTCPSession::asyncRecv(int recvBufferSize, UAsyncCallback callback) {
		this->recvBuffer.resize(recvBufferSize);

		auto self(shared_from_this());
		boost::asio::async_write(this->socket, boost::asio::buffer(this->recvBuffer),
			[=](boost::system::error_code ec, std::size_t bytesRecv) {
				if (!ec && bytesRecv > 0) {
					callback(this->recvBuffer, bytesRecv);
				}
			});
	}

	void UTCPSession::asyncRecv(UAsyncCallback callback) {
		auto self(shared_from_this());
		boost::asio::async_read(this->socket, boost::asio::dynamic_buffer(this->recvBuffer),
			[=](boost::system::error_code ec, std::size_t bytesRecv) {
				if (!ec && bytesRecv > 0) {
					callback(this->recvBuffer, bytesRecv);
				}
			});
	}
};