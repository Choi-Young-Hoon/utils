#pragma once

#include <thread>
#include <memory>
#include <functional>

namespace utils {
    class UTimerInterface {
    public:
        explicit UTimerInterface(unsigned long milliseconds);
        virtual ~UTimerInterface();

    public:
        bool start();
        void stop();

    protected:
        virtual void run() = 0;

    private:
        void timer();

    private:
        bool isRunning;

        unsigned long milliseconds;

        std::function<void()> timerFunction;

        std::shared_ptr<std::thread> timerThread;
    };
};