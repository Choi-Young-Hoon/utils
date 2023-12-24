#include "gtest/gtest.h"

#include "ULogger.hpp"
#include "UThread.hpp"

#include <fstream>

TEST(ULogger, ULoggerTest) {
    std::remove("./test.txt");

    utils::ULogger& logger = utils::ULogger::getInstance();
    ASSERT_TRUE(logger.createLogger("./test.txt"));
    utils::ULoggerIOWriterPtr loggerWriter = logger.getLoggerIOWriter("./test.txt");
    ASSERT_TRUE(loggerWriter != nullptr);
    ASSERT_TRUE(loggerWriter->write(utils::LOG_LEVEL::INFO, "hello log", __FILE__, __LINE__));

    utils::ULoggerIOWriterPtr loggerWriterIsNULL = logger.getLoggerIOWriter("./test2.txt");
    ASSERT_TRUE(loggerWriterIsNULL == nullptr);
}

TEST(ULogger, ULoggerDefineTest) {
    std::remove("./macro.txt");

    utils::ULogger& logger = utils::ULogger::getInstance();
    ASSERT_TRUE(logger.createLogger("./macro.txt"));

    utils::ULoggerIOWriterPtr loggerWriter = logger.getLoggerIOWriter("./macro.txt");
    ASSERT_TRUE(loggerWriter != nullptr);

    LOG_WRITE_INFO(loggerWriter, "INFO Log Test");
    LOG_WRITE_ERROR(loggerWriter, "ERROR Log Test");
}

TEST(ULogger, ULoggerMultiThreadTest) {
    std::remove("./thread_log.txt");

    utils::ULogger& logger = utils::ULogger::getInstance();
    ASSERT_TRUE(logger.createLogger("./thread_log.txt"));

    utils::ULoggerIOWriterPtr  loggerWriter = logger.getLoggerIOWriter("./thread_log.txt");

    int threadNumber = 0;
    int threadCount  = 10;
    std::vector<std::thread> threadList;
    for (int i = 0; i < threadCount; i++) {
        threadList.emplace_back(std::thread([&](int threadNumber){
            for (int i = 0; i < 1000; i++) {
                LOG_WRITE_INFO(loggerWriter, "INFO thread_number: " + std::to_string(threadNumber));
            }
        }, threadNumber));
        threadNumber++;
    }

    for (auto& iter : threadList) {
        iter.join();
    }

    while (loggerWriter->getTaskQueueSize() != 0) {
        continue;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::vector<int> logCount(threadCount, 0);
    std::ifstream inputStream("./thread_log.txt");
    ASSERT_TRUE(inputStream.fail() == false);

    std::string line;
    while (std::getline(inputStream, line)) {
        int number = line[line.length() - 1] - '0';

        logCount[number]++;
    }

    for (auto iter : logCount) {
        ASSERT_TRUE(iter == 1000);
    }
}