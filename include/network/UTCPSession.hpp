#pragma once

#include "boost/asio.hpp"

#include "type/ByteBuffer.hpp"

#include <memory>

#define TCP_SERVER_BUFFER_SIZE 4096

namespace utils {
	class UTCPSession : public std::enable_shared_from_this<UTCPSession> {
	public:
		explicit UTCPSession(boost::asio::ip::tcp::socket socket);
		virtual ~UTCPSession();

	public:
		int recv(ByteBuffer* buffer);
		int send(const ByteBuffer& buffer);

	private:
		boost::asio::ip::tcp::socket socket;

		std::array<unsigned char, TCP_SERVER_BUFFER_SIZE> recvBuffer;
	};
};