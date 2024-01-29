#include "thread/UTimerManager.hpp"

namespace utils {
    UTimerManager::UTimerManager() {

    }

    UTimerManager::~UTimerManager() {

    }

    bool UTimerManager::start() {
        for (auto& iter : this->timerList) {
            if (iter->start() == false) {
                this->stop();
                return false;
            }
        }

        return true;
    }

    void UTimerManager::stop() {
        for (auto& iter : this->timerList) {
            iter->stop();
        }
    }

    void UTimerManager::attachTimer(utils::UTimerInterface &timer) {
        this->timerList.emplace_back(&timer);
    }

    size_t UTimerManager::getTimerCount() {
        return this->timerList.size();
    }
}