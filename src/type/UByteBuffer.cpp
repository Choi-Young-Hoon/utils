#include "type/UByteBuffer.hpp"

namespace utils {
	UByteBuffer::UByteBuffer() {

	}

	UByteBuffer::UByteBuffer(std::string& str) {
		this->setText(str);
	}

	UByteBuffer::UByteBuffer(std::string&& str) {
		this->setText(str);
	}

	UByteBuffer::UByteBuffer(unsigned char* data, int length) {
		this->setData(data, length);
	}

	UByteBuffer::~UByteBuffer() {

	}

	void UByteBuffer::setText(std::string& str) {
		this->clear();
		this->insert(this->begin(), str.begin(), str.end());
	}

	void UByteBuffer::setData(unsigned char* data, int length) {
		this->clear();
		this->insert(this->begin(), data, data + length);
	}

	void UByteBuffer::append(unsigned char* data, int length) {
		this->insert(this->end(), data, data + length);
	}
}