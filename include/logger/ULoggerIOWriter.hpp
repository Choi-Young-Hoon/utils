#pragma once

#include <thread>
#include <queue>
#include <memory>
#include <fstream>

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
        bool write(std::string&& text, std::string&& sourceFile = "", int line = 0);

    private:
        std::fstream fileStream;

        UThreadPool<void> threadPool;
    };

    typedef std::shared_ptr<ULoggerIOWriter> ULoggerIOWriterPtr;
}