#include "network/UUDPClient.hpp"

#include <iostream>

namespace utils {
	UUDPClient::UUDPClient(std::string& serverIpAddress, unsigned short port) 
	: socket(this->ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0))
	{
		this->serverIpAddress = serverIpAddress;
		this->port			  = port;		
		this->createEndpoint();
	}

	UUDPClient::UUDPClient(std::string&& serverIpAddress, unsigned short port) 
	: socket(this->ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0))
	{
		this->serverIpAddress = serverIpAddress;
		this->port			  = port;		
		this->createEndpoint();
	}

	UUDPClient::~UUDPClient() {

	}

	void UUDPClient::closeSocket() {
		this->socket.close();
	}

	size_t UUDPClient::recv(UByteBuffer* buffer, int recvBufferSize, UResult* result) {
		if (result == nullptr ||
			buffer == nullptr) {
			return -1;
		}
		buffer->resize(recvBufferSize);
		
		boost::system::error_code error;
		size_t size = this->socket.receive_from(boost::asio::buffer(*buffer), this->receiverEndpoint, 0, error);
		if (error) {
			std::cout << "UUDPClient::recv error: " << error.message() << std::endl;
			return result->failedReturnValue(error.value(), error.message());
		}

		return result->successReturnValue(size);
	}

	size_t UUDPClient::send(const UByteBuffer& buffer, UResult* result) {
		if (result == nullptr) {
			return -1;
		}

		boost::system::error_code error;
		size_t size = this->socket.send_to(boost::asio::buffer(buffer), this->receiverEndpoint, 0, error);
		if (error) {
			return result->failedReturnValue(error.value(), error.message());
		}

		return result->successReturnValue(size);
	}

	void UUDPClient::asyncRecv(int recvBufferSize, UAsyncCallback callback) {
		this->recvBuffer.resize(recvBufferSize);
		this->socket.async_receive_from(boost::asio::buffer(this->recvBuffer), this->receiverEndpoint,
			[=](boost::system::error_code ec, std::size_t bytesReceived) {
				if (!ec && bytesReceived > 0) {
					callback(this->recvBuffer, bytesReceived);
				}
			}
		);
	}

	void UUDPClient::asyncSend(const UByteBuffer& buffer) {
		this->socket.async_send_to(boost::asio::buffer(buffer), this->receiverEndpoint,
			[this](boost::system::error_code ec, std::size_t bytesSent) {
				if (!ec && bytesSent > 0) {
					
				}
			}
		);
	}

	void UUDPClient::createEndpoint() {
		boost::asio::ip::udp::resolver resolver(this->ioService);
		boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), this->serverIpAddress, std::to_string(this->port));
		this->receiverEndpoint = *resolver.resolve(query);
	}
}