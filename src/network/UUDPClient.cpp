#include "network/UUDPClient.hpp"

#include <iostream>

namespace utils {
	UUDPClient::UUDPClient(std::string&& serverIpAddress, unsigned short port) 
	: socket(this->ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0))
	{
		boost::asio::ip::udp::resolver resolver(this->ioService);
		boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), serverIpAddress, std::to_string(port));
		this->receiverEndpoint = *resolver.resolve(query);
	}

	UUDPClient::~UUDPClient() {

	}

	int UUDPClient::recv(ByteBuffer* buffer) {
		boost::system::error_code ec;
		int size = this->socket.receive_from(boost::asio::buffer(this->recvBuffer), this->receiverEndpoint, 0, ec);
		if (ec) {
			std::cout << __FUNCTION__ << " Error: " << ec.message() << std::endl;
			return ec.value();
		}

		buffer->setData(this->recvBuffer.data(), size);

		return size;
	}

	int UUDPClient::send(const ByteBuffer& buffer) {
		boost::system::error_code ec;
		int size = this->socket.send_to(boost::asio::buffer(buffer), this->receiverEndpoint, 0, ec);
		if (ec) {
			std::cout << __FUNCTION__ << " Error: " << ec.message() << std::endl;
			return ec.value();
		}

		return size;
	}

	void UUDPClient::asyncRecv(UDPClientCallback callback) {
		this->socket.async_receive_from(boost::asio::buffer(this->recvBuffer), this->receiverEndpoint,
			[=](boost::system::error_code ec, std::size_t bytesReceived) {
				if (!ec && bytesReceived > 0) {
					std::cout << "Received " << bytesReceived << " bytes from " << this->receiverEndpoint.address().to_string() << ":" << this->receiverEndpoint.port() << std::endl;

					ByteBuffer buffer;
					buffer.setData(this->recvBuffer.data(), this->recvBuffer.size());
					callback(buffer);
				}
			}
		);
	}

	void UUDPClient::asyncSend(const ByteBuffer& buffer) {
		this->socket.async_send_to(boost::asio::buffer(buffer), this->receiverEndpoint,
			[this](boost::system::error_code ec, std::size_t bytesSent) {
				if (!ec && bytesSent > 0) {
					std::cout << "Sent " << bytesSent << " bytes to " << this->receiverEndpoint.address().to_string() << ":" << this->receiverEndpoint.port() << std::endl;
				}
			}
		);
	}
}