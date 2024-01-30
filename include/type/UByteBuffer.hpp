#pragma once

#include <vector>
#include <string>

namespace utils {
	class UByteBuffer : public std::vector<unsigned char> {
	public:
		explicit UByteBuffer();
		explicit UByteBuffer(std::string& str);
		explicit UByteBuffer(std::string&& str);
		explicit UByteBuffer(unsigned char* data, int length);
		virtual ~UByteBuffer();

	public:
		void setText(std::string& str);
		
		void setData(unsigned char* data, int length);
		void setData(UByteBuffer& buffer);

		void append(unsigned char* data, int length);
		void append(UByteBuffer& buffer);

	private:

	};
}