#include "type/ByteBuffer.hpp"

namespace utils {
	ByteBuffer::ByteBuffer() {

	}

	ByteBuffer::ByteBuffer(std::string& str) {
		this->setText(str);
	}

	ByteBuffer::ByteBuffer(std::string&& str) {
		this->setText(str);
	}

	ByteBuffer::~ByteBuffer() {

	}

	void ByteBuffer::setText(std::string& str) {
		this->clear();
		this->insert(this->begin(), str.begin(), str.end());
	}

	void ByteBuffer::setData(unsigned char* data, int length) {
		this->clear();
		this->insert(this->begin(), data, data + length);
	}

	void ByteBuffer::append(unsigned char* data, int length) {
		this->insert(this->end(), data, data + length);
	}
}