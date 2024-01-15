#include "network/UUDPServer.hpp"

#include <iostream>

namespace utils {
	UUDPServer::UUDPServer(unsigned short port) {
		this->port = port;
	}

	UUDPServer::~UUDPServer() {
		
	}

	bool UUDPServer::start() {
		try {
			this->socket = std::make_unique<boost::asio::ip::udp::socket>(this->ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), this->port));
		} catch (std::exception& e) {
			std::cerr << "Start Server Error: " << e.what() << std::endl;
			return false;
		}
		this->ioService.run();

		return true;
	}

	void UUDPServer::stop() {
		this->socket->close();
		this->ioService.stop();
	}	

	int UUDPServer::recv(ByteBuffer* buffer) {
		boost::system::error_code ec;

		int size = this->socket->receive_from(boost::asio::buffer(this->recvBuffer), this->endpoint, 0, ec);
		if (ec) {
			std::cout << __FUNCTION__<< " Error: " <<  ec.message() << std::endl;
			return ec.value();
		}

		buffer->setData(this->recvBuffer.data(), size);
	
		return size;
	}

	int UUDPServer::send(const ByteBuffer& buffer) {
		boost::system::error_code ec;
		int size = this->socket->send_to(boost::asio::buffer(buffer), this->endpoint, 0, ec);
		if (ec) {
			std::cout << __FUNCTION__ << " Error: " << ec.message() << std::endl;
			return ec.value();
		}

		return size;
	}

	void UUDPServer::asyncRecv(UDPServerCallback callback) {
		this->socket->async_receive_from(boost::asio::buffer(this->recvBuffer), this->endpoint, 
			[=](boost::system::error_code ec, std::size_t bytesReceived) {
				if (!ec && bytesReceived > 0) {
					std::cout << "Received " << bytesReceived << " bytes from " << this->endpoint.address().to_string() << ":" << this->endpoint.port() << std::endl;

					ByteBuffer buffer;
					buffer.setData(this->recvBuffer.data(), bytesReceived);
					callback(buffer);
				}
			}
		);
	}

	void UUDPServer::asyncSend(const ByteBuffer& buffer) {
		this->socket->async_send_to(boost::asio::buffer(buffer), this->endpoint,
			[this](boost::system::error_code ec, std::size_t bytesSent) {
				if (!ec && bytesSent > 0) {
					std::cout << "Sent " << bytesSent << " bytes to " << this->endpoint.address().to_string() << ":" << this->endpoint.port() << std::endl;
				}
			}
		);
	}
};