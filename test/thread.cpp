#include "gtest/gtest.h"

#include "thread/UThreadPool.hpp"

#include <iostream>

TEST(THREAD, UThreadPool) {
    utils::UThreadPool<int> threadPool;

    ASSERT_TRUE(threadPool.getThreadCount() == std::thread::hardware_concurrency());

    auto taskResult = threadPool.enqueue([&](){
        return 100;
    });

    int result = taskResult.get();
    ASSERT_TRUE(result == 100);
}