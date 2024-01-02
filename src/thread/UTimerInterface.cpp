#include "thread/UTimerInterface.hpp"

#include <chrono>
#include <memory>

namespace utils {
    UTimerInterface::UTimerInterface(unsigned long milliseconds) {
        this->isRunning = false;
        this->milliseconds = milliseconds;
    }

    UTimerInterface::~UTimerInterface() {
        this->stop();
    }

    bool UTimerInterface::start() {
        this->isRunning = true;
        try {
            this->timerThread = std::make_shared<std::thread>([this](){
                this->timer();
            });
        } catch (std::bad_alloc& e) {
            return false;
        }

        return true;
    }

    void UTimerInterface::stop() {
        this->isRunning = false;

        if (this->timerThread->joinable() == false) {
            return;
        }
        this->timerThread->join();
    }

    void UTimerInterface::timer() {
        auto startTime = std::chrono::steady_clock::now();

        while (this->isRunning) {
            auto endTime = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

            unsigned long elapsedTime = static_cast<unsigned long>(elapsed);
            if (elapsedTime >= this->milliseconds) {
                this->run();
                startTime = endTime;
            }

            std::this_thread::sleep_for(std::chrono::microseconds(10));
        }
    }
}