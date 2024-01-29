#pragma once

#include "network/UNetworkDefine.hpp"

#include "type/UResult.hpp"
#include "type/UByteBuffer.hpp"

#include <vector>
#include <functional>

#include "boost/asio.hpp"

namespace utils {
	class UUDPServer {
	public:
		explicit UUDPServer(unsigned short port);
		virtual ~UUDPServer();

	public:
		void closeSocket();

		// Sync
		size_t recv(UByteBuffer* buffer, int recvBufferSize, UResult* result);
		size_t send(const UByteBuffer& buffer, UResult* result);

		// Async
		bool asyncServiceRun();
		void asyncServiceStop();
		void asyncRecv(int recvBufferSize, UAsyncCallback callback);
		void asyncSend(const UByteBuffer& buffer);

	private:
		boost::asio::io_service ioService;
		std::unique_ptr<boost::asio::ip::udp::socket> socket;
		boost::asio::ip::udp::endpoint endpoint;

		UByteBuffer recvBuffer;
	};
};