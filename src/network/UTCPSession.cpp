#include "network/UTCPSession.hpp"

#include <iostream>

namespace utils {
	UTCPSession::UTCPSession(boost::asio::ip::tcp::socket socket)
	: socket(std::move(socket))
	{

	}

	UTCPSession::~UTCPSession() {

	}

	int UTCPSession::recv(ByteBuffer* buffer) {
		boost::system::error_code error;
		
		int size = this->socket.read_some(boost::asio::buffer(this->recvBuffer), error);
		if (error = boost::asio::error::eof) {
			// 클라이언트 연결 종료
			std::cout << __FUNCTION__ << " Clinet close " << error.message() << std::endl;
			return -1;
		} else if (error) {
			// 에러 처리
			std::cout << __FUNCTION__ << " Error: " << error.message() << std::endl;
			return error.value();
		}

		buffer->setData(this->recvBuffer.data(), size);

		return size;
	}

	int UTCPSession::send(const ByteBuffer& buffer) {
		boost::system::error_code error;

		int size = this->socket.write_some(boost::asio::buffer(buffer), error);
		if (error) {
			// 에러 처리
			std::cout << __FUNCTION__ << " Error: " << error.message() << std::endl;
			return error.value();
		}
		return 0;
	}
};