#include "logger/ULoggerIOWriter.hpp"

#include <sstream>
#include <chrono>
#include <iomanip>
#include <format>


namespace utils {
    std::shared_ptr<ULoggerIOWriter> ULoggerIOWriter::createLogger(std::string& filePath) {
        std::shared_ptr<ULoggerIOWriter> ioWriter;
        try {
            ioWriter = std::make_shared<ULoggerIOWriter>();
        } catch (std::bad_alloc& e) {
            return nullptr;
        }

        if (ioWriter->open(filePath) == false) {
            return nullptr;
        }

        return ioWriter;
    }

    ULoggerIOWriter::ULoggerIOWriter()
    : threadPool(1) {

    }

    ULoggerIOWriter::~ULoggerIOWriter() {

    }

    bool ULoggerIOWriter::open(std::string& filePath) {
        this->fileStream.open(filePath, std::fstream::in | std::fstream::out | std::fstream::app);
        return this->fileStream.is_open();
    }

    bool ULoggerIOWriter::isOpen() {
        return this->fileStream.is_open();
    }

    bool ULoggerIOWriter::write(LOG_LEVEL logLevel, std::string&& text, std::string&& sourceFile, int sourceLine) {
        std::string log = std::format("{0} {1} Line: {2} - [{3}] {4}\n", this->getLogTime()
                                                                            , sourceFile
                                                                            , sourceLine
                                                                            , logLevelToString(logLevel)
                                                                            , text);
        this->threadPool.enqueue([this](std::string log){
            this->fileStream << log;
            this->fileStream.flush();
        }, log);

        return true;
    }

    void ULoggerIOWriter::close() {
        this->fileStream.close();
    }

    void ULoggerIOWriter::stop() {
        this->threadPool.stop();
    }

    unsigned int ULoggerIOWriter::getTaskQueueSize() {
        return this->threadPool.getTaskQueueSize();
    }

    std::string ULoggerIOWriter::getLogTime() {
        auto now = std::chrono::system_clock::now();

        return std::format("{:%Y-%m-%d %H:%M:%S}", now);
    }

};