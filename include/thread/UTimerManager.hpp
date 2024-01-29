#pragma once

#include "thread/UTimerInterface.hpp"

#include <vector>

namespace utils {
    class UTimerManager {
    public:
        explicit UTimerManager();
        virtual ~UTimerManager();

    public:
        bool start();
        void stop();

        void attachTimer(UTimerInterface& timer);

    public: // getter setter
        size_t getTimerCount();

    private:
        std::vector<UTimerInterface*> timerList;
    };
}