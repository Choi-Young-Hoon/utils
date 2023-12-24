#include "gtest/gtest.h"

#include "thread/UThreadPool.hpp"

#include <iostream>

TEST(THREAD, UThreadPool) {
    utils::UThreadPool<int> threadPool;


    std::cout << "CPU Core Count: " << std::thread::hardware_concurrency() << std::endl;
    std::cout << "ThreadPool Thread Count: " << threadPool.getThreadCount() << std::endl;
    ASSERT_TRUE(threadPool.getThreadCount() == std::thread::hardware_concurrency());

    auto taskResult = threadPool.enqueue([&](){
        return 100;
    });

    int result = taskResult.get();
    std::cout << "Result: " << result << std::endl;
    ASSERT_TRUE(result == 100);
}