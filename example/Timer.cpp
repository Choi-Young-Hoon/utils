#include "UThread.hpp"


/// 1 Seconds timer
class Timer1Sec : public utils::UTimerInterface {
public:
    explicit Timer1Sec(): utils::UTimerInterface(1000)
    {}


    virtual ~Timer1Sec()
    {}

protected:
    virtual void run() override {
        std::cout << "1 Sec!!" << std::endl;
    }
};



int main(void) {
    Timer1Sec timer1Sec1;
    Timer1Sec timer1Sec2;

    utils::UTimerManager timerManager;
    timerManager.attachTimer(timer1Sec1);
    timerManager.attachTimer(timer1Sec2);
    if (timerManager.start() == false) {
        return false;
    }

    std::this_thread::sleep_for(std::chrono::seconds (5));
    timerManager.stop();
    return 0;
}