#pragma once

#include <vector>
#include <string>

namespace utils {
	class ByteBuffer : public std::vector<unsigned char> {
	public:
		explicit ByteBuffer();
		explicit ByteBuffer(std::string& str);
		explicit ByteBuffer(std::string&& str);
		virtual ~ByteBuffer();

	public:
		void setText(std::string& str);
		void setData(unsigned char* data, int length);
		void append(unsigned char* data, int length);

	private:

	};
}