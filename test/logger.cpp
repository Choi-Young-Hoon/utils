#include "gtest/gtest.h"

#include "logger/ULogger.hpp"
#include "logger/ULoggerIOWriter.hpp"

TEST(ULogger, ULoggerTest) {
    utils::ULogger& logger = utils::ULogger::getInstance();
    ASSERT_TRUE(logger.createLogger("./test.txt"));
    utils::ULoggerIOWriterPtr loggerWriter = logger.getLoggerIOWriter("./test.txt");
    ASSERT_TRUE(loggerWriter != nullptr);
    ASSERT_TRUE(loggerWriter->write("hello log", __FILE__, __LINE__));

    utils::ULoggerIOWriterPtr loggerWriterIsNULL = logger.getLoggerIOWriter("./test2.txt");
    ASSERT_TRUE(loggerWriterIsNULL == nullptr);
}

TEST(ULoggerIOWriter, ULoggerIOWriterTest) {

}