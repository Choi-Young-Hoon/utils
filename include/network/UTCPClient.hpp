#pragma once

#include "network/UNetworkDefine.hpp"

#include "type/UResult.hpp"
#include "type/UByteBuffer.hpp"

#include <string>
#include <memory>
#include <functional>

#include "boost/asio.hpp"

namespace utils {
	class UTCPClient {
	public:
		explicit UTCPClient(std::string& serverIpAddress, unsigned short port);
		explicit UTCPClient(std::string&& serverIpAddress, unsigned short port);
		virtual ~UTCPClient();

	public:
		bool connect(UResult* result);
		void close();

		// Sync
		size_t recvUntil(UByteBuffer* buffer, const std::string& until, UResult* result);
		size_t recv(UByteBuffer* buffer, int recvBufferSize, UResult* result);
		size_t send(const UByteBuffer& buffer, UResult* result);

		// Async
		void asyncRecv(int recvBufferSize, UAsyncCallback callback);
		void asyncSend(const UByteBuffer& buffer);

	private:
		std::string serverIpAddress;
		unsigned short port;

		boost::asio::io_context ioContext;
		boost::asio::ip::tcp::endpoint endpoint;
		std::shared_ptr<boost::asio::ip::tcp::socket> socket;

		UByteBuffer recvBuffer;
	};
};