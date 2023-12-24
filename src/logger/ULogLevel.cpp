#include "logger/ULogLevel.hpp"

#include <string>

namespace utils {
    std::string logLevelToString(LOG_LEVEL logLevel) {
        std::string level;

        switch (logLevel) {
            case LOG_LEVEL::INFO:  level = "INFO";  break;
            case LOG_LEVEL::ERROR: level = "ERROR"; break;
        }

        return level;
    }
};