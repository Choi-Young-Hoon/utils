#pragma once

#include "type/UResult.hpp"
#include "type/UByteBuffer.hpp"

#include <functional>

namespace utils {
	typedef std::function<void(UByteBuffer&, size_t)> UAsyncCallback;
	typedef std::function<void(UResult&)>     UAsyncErrorCallback;
};