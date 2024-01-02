#include "gtest/gtest.h"
#include "UThread.hpp"


/// 1 Seconds timer
class Timer1Sec : public utils::UTimerInterface {
public:
    explicit Timer1Sec()
    : utils::UTimerInterface(1000) {}

    virtual ~Timer1Sec() {}

protected:
    virtual void run() override {
        std::cout << "1 Sec!!" << std::endl;
    }
};

/// 2 Seconds Timer
class Timer2Sec : public utils::UTimerInterface {
public:
    explicit Timer2Sec()
    : utils::UTimerInterface(2000) {}

    virtual ~Timer2Sec() {}

protected:
    virtual void run() override {
        std::cout << "2 Sec!!" << std::endl;
    }
};


TEST(THREAD, UTimerInterface) {
    Timer1Sec timer1Sec;
    Timer2Sec timer2Sec;

    ASSERT_TRUE(timer1Sec.start());
    ASSERT_TRUE(timer2Sec.start());

    std::this_thread::sleep_for(std::chrono::seconds (4));

    timer1Sec.stop();
    timer2Sec.stop();
}

TEST(THREAD, UTimerManager) {
    Timer1Sec timer1Sec1;
    Timer1Sec timer1Sec2;
    Timer2Sec timer2Sec1;
    Timer2Sec timer2Sec2;

    utils::UTimerManager timerManager;
    timerManager.attachTimer(timer1Sec1);
    timerManager.attachTimer(timer1Sec2);
    timerManager.attachTimer(timer2Sec1);
    timerManager.attachTimer(timer2Sec2);
    ASSERT_TRUE(timerManager.start());

    std::this_thread::sleep_for(std::chrono::seconds (5));
    timerManager.stop();
}