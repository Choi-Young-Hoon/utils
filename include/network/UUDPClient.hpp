#pragma once

#include "network/UNetworkDefine.hpp"

#include "type/UResult.hpp"
#include "type/UByteBuffer.hpp"

#include <vector>
#include <functional>

#include "boost/asio.hpp"

namespace utils {
	class UUDPClient {
	public:
		explicit UUDPClient(std::string& serverIpAddress, unsigned short port);
		explicit UUDPClient(std::string&& serverIpAddress, unsigned short port);
		virtual ~UUDPClient();

	public:
		void closeSocket();

		// Sync
		size_t recv(UByteBuffer* buffer, int recvBufferSize, UResult* result);
		size_t send(const UByteBuffer& buffer, UResult* result);

		// Async
		void asyncRecv(int recvBufferSize, UAsyncCallback callback);
		void asyncSend(const UByteBuffer& buffer);

	private:
		void createEndpoint();

	private:
		unsigned short port;
		std::string serverIpAddress;

		boost::asio::io_service ioService;
		boost::asio::ip::udp::socket socket;
		boost::asio::ip::udp::endpoint receiverEndpoint;

		UByteBuffer recvBuffer;
	};
};