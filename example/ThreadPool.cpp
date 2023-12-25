#include "thread/UThreadPool.hpp"

int main() {
    utils::UThreadPool<int> threadPool;

    auto taskResult1 = threadPool.enqueue([](){
        return 100;
    });

    auto taskResult2 = threadPool.enqueue([](){
        return 1000;
    });

    std::cout << "ThreadResult: " << taskResult1.get() << std::endl;
    std::cout << "ThreadReuslt: " << taskResult2.get() << std::endl;

    return 0;
}