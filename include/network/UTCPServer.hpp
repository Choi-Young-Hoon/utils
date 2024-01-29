#pragma once

#include "network/UNetworkDefine.hpp"
#include "network/UTCPSession.hpp"

#include "type/UResult.hpp"
#include "type/UByteBuffer.hpp"

#include <memory>

#include "boost/asio.hpp"

namespace utils {
	typedef std::function<void(UTCPSessionPtr)> UAcceptCallback;

	class UTCPServer {
	public:
		explicit UTCPServer(unsigned short port);
		virtual ~UTCPServer();

	public:
		bool createAcceptor(UResult* result);
		void closeAccpetor();

		// Sync
		UTCPSessionPtr accept(UResult* result);

		// Async
		bool asyncServiceRun();
		void asyncServiceStop();
		void asyncAccept(UAcceptCallback callback);

	private:
		unsigned short port;

		boost::asio::io_service ioService;
		std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor;
	};
};