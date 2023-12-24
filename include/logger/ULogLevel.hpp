#pragma once

#include <string>

namespace utils {
    enum class LOG_LEVEL {
        INFO = 0,
        ERROR
    };

    std::string logLevelToString(LOG_LEVEL logLevel);
};