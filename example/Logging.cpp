#pragma once

#include "ULogger.hpp"

int main() {
    utils::ULogger& logger = utils::ULogger::getInstance();
    if (logger.createLogger("./hello_world.txt") == false) {
        std::cout << "Logger create failed" << std::endl;
        return -1;
    }

    utils::ULoggerIOWriterPtr loggerIoWriter = logger.getLoggerIOWriter("./hello_world.txt");
    if (loggerIoWriter == nullptr) {
        std::cout << "Not found ULoggerIOWriter" << std::endl;
        return -1;
    }

    LOG_WRITE_INFO(loggerIoWriter, "Info Log Write!!!!!");
    LOG_WRITE_ERROR(loggerIoWriter, "Error Log Write!!!!!");

    return 0;
}