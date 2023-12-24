#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "logger/ULoggerIOWriter.hpp"

namespace utils {
    class ULogger {
    public: // static method
        static ULogger& getInstance();

    public:
        bool createLogger(std::string&& filePath);

        ULoggerIOWriterPtr getLoggerIOWriter(std::string&& filePath);

        void stop();

    private:
        explicit ULogger();
        virtual ~ULogger();

    private: // Single object
        static ULogger instance;

    private:
        std::unordered_map<std::string, std::shared_ptr<ULoggerIOWriter>> loggerIOWriterMap;
    };
};