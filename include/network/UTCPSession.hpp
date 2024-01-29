#pragma once

#include "network/UNetworkDefine.hpp"

#include "type/UResult.hpp"
#include "type/UByteBuffer.hpp"

#include <vector>
#include <memory>
#include <functional>

#include "boost/asio.hpp"

namespace utils {
	class UTCPSession : public std::enable_shared_from_this<UTCPSession> {
	public:
		explicit UTCPSession(boost::asio::ip::tcp::socket socket);
		virtual ~UTCPSession();

	public:
		static std::shared_ptr<UTCPSession> createSession(boost::asio::ip::tcp::socket socket);

	public:
		void closeSocket();

		// Sync
		size_t recv(UByteBuffer* buffer, int recvBufferSize, UResult* result);
		size_t send(const UByteBuffer& buffer, UResult* result);

		// Async
		void asyncRecv(int recvBufferSize, UAsyncCallback callback);
		void asyncRecv(UAsyncCallback callback);
		void asyncSend(const UByteBuffer& buffer);

	private:
		boost::asio::ip::tcp::socket socket;

		UByteBuffer recvBuffer;
	};
	typedef std::shared_ptr<UTCPSession> UTCPSessionPtr;
};