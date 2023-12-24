#include "logger/ULoggerIOWriter.hpp"

#include <sstream>
#include <chrono>
#include <iomanip>
#include <ctime>

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

        std::stringstream log;
        log << this->getLogTime() << " " << sourceFile << " Line: " << sourceLine << " - [" << logLevelToString(logLevel) << "] " << text << std::endl;

        this->threadPool.enqueue([this](std::string log){
            this->fileStream << log;
            this->fileStream.flush();
        }, log.str());

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
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::tm tm       = *std::localtime(&time);

        auto miliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        std::stringstream stringStream;
        stringStream << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        stringStream << "." << std::setfill('0') << std::setw(3) << miliseconds.count();

        return stringStream.str();
    }

};