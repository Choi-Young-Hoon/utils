#include "network/UTCPServer.hpp"
#include "network/UTCPSession.hpp"

namespace utils {
	UTCPServer::UTCPServer(unsigned short port) {
		this->port = port;
	}

	UTCPServer::~UTCPServer() {

	}

	bool UTCPServer::createAcceptor(UResult* result) {
		if (result == nullptr) {
			return false;
		}

		try {
			this->acceptor = std::make_shared<boost::asio::ip::tcp::acceptor>(this->ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), this->port));
		} catch (std::exception& e) {
			return result->failed(-1, e.what());
		}
		return result->success();
	}

	void UTCPServer::closeAccpetor() {
		if (this->acceptor != nullptr) {
			this->acceptor->close();
		}
	}

	bool UTCPServer::asyncServiceRun() {
		this->ioService.run();

		return true;
	}

	void UTCPServer::asyncServiceStop() {
		this->ioService.stop();
	}

	UTCPSessionPtr UTCPServer::accept(UResult* result) {
		if (result == nullptr) {
			return nullptr;
		}

		boost::system::error_code error;
		boost::asio::ip::tcp::socket socket = this->acceptor->accept(this->ioService, error);
		if (error) {
			result->failed(error.value(), error.message());
			return nullptr;
		}

		result->success();
		return UTCPSession::createSession(std::move(socket));
	}

	void UTCPServer::asyncAccept(UAcceptCallback callback) {
		this->acceptor->async_accept(
			[this, callback](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
				if (!ec) {
					UTCPSessionPtr session = UTCPSession::createSession(std::move(socket));
					callback(session);
					this->asyncAccept(callback);
				}
			}
		);
	}
}	