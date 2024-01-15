#pragma once

#include "boost/asio.hpp"

#include "type/ByteBuffer.hpp"

#define UDP_CLIENT_BUFFER_SIZE 4096

namespace utils {
	typedef std::function<void(ByteBuffer&)> UDPClientCallback;
	class UUDPClient {
	public:
		explicit UUDPClient(std::string&& serverIpAddress, unsigned short port);
		virtual ~UUDPClient();

	public:
		// Sync
		int recv(ByteBuffer* buffer);
		int send(const ByteBuffer& buffer);

		// Async
		void asyncRecv(UDPClientCallback callback);
		void asyncSend(const ByteBuffer& buffer);

	private:
		boost::asio::io_service ioService;
		boost::asio::ip::udp::socket socket;
		boost::asio::ip::udp::endpoint receiverEndpoint;

		std::array<unsigned char, UDP_CLIENT_BUFFER_SIZE> recvBuffer;
	};
};