#pragma once

#include <thread>
#include <queue>
#include <memory>
#include <fstream>

#include "logger/ULogLevel.hpp"
#include "thread/UThreadPool.hpp"

namespace utils {
    class ULoggerIOWriter {
    public:
        static std::shared_ptr<ULoggerIOWriter> createLogger(std::string& filePath);

    public:
        explicit ULoggerIOWriter();
        virtual ~ULoggerIOWriter();

    public:
        bool open(std::string& filePath);
        bool isOpen();
        bool write(LOG_LEVEL logLevel, std::string&& text, std::string&& sourceFile = "", int sourceLine = 0);
        void close();
        void stop();

        unsigned int getTaskQueueSize();

    private:
        std::string getLogTime();

    private:
        std::fstream fileStream;

        UThreadPool<void> threadPool;
    };

    typedef std::shared_ptr<ULoggerIOWriter> ULoggerIOWriterPtr;
}