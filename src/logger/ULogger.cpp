#include "logger/ULogger.hpp"

namespace utils {
    ULogger ULogger::instance;
    ULogger& ULogger::getInstance() {
        return ULogger::instance;
    }

    ULogger::ULogger() {

    }

    ULogger::~ULogger() {

    }

    bool ULogger::createLogger(std::string&& filePath) {
        ULoggerIOWriterPtr loggerIOWriter = ULoggerIOWriter::createLogger(filePath);
        if (loggerIOWriter == nullptr) {
            return false;
        }

        this->loggerIOWriterMap[filePath] = loggerIOWriter;
        return true;
    }

    ULoggerIOWriterPtr ULogger::getLoggerIOWriter(std::string&& filePath) {
        auto iter = this->loggerIOWriterMap.find(filePath);
        if (iter == this->loggerIOWriterMap.end()) {
            return nullptr;
        }
        return this->loggerIOWriterMap[filePath];
    }

    void ULogger::stop() {
        for (auto& iter : this->loggerIOWriterMap) {
            iter.second->close();
            iter.second->stop();
        }

        this->loggerIOWriterMap.clear();
    }
}