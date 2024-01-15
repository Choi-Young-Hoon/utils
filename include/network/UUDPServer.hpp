#pragma once

#include "boost/asio.hpp"

#include "type/ByteBuffer.hpp"

#define UDP_SERVER_BUFFER_SIZE 4096

namespace utils {
	typedef std::function<void(ByteBuffer&)> UDPServerCallback;
	
	class UUDPServer {
	public:
		explicit UUDPServer(unsigned short port);
		virtual ~UUDPServer();

	public:
		bool start();
		void stop();

		// Sync
		int recv(ByteBuffer* buffer);
		int send(const ByteBuffer& buffer);

		// Async
		void asyncRecv(UDPServerCallback callback);
		void asyncSend(const ByteBuffer& buffer);

	private:
		int port;
		
		boost::asio::io_service ioService;
		std::unique_ptr<boost::asio::ip::udp::socket> socket;
		boost::asio::ip::udp::endpoint endpoint;

		std::array<unsigned char, UDP_SERVER_BUFFER_SIZE> recvBuffer;
	};
};