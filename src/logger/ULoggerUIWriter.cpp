#include "logger/ULoggerIOWriter.hpp"

#include <sstream>

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

    bool ULoggerIOWriter::write(std::string&& text, std::string&& sourceFile, int line) {
        std::stringstream log;
        log << sourceFile << " " << line << " - " << text << std::endl;
        this->threadPool.enqueue([this](std::string log){
            this->fileStream << log;
        }, log.str());
        return true;
    }

};