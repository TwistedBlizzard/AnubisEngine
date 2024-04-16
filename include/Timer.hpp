#ifndef TIMER_H
#define TIMER_H

#include "Timing.hpp"

class Timer
{
public:
    Timer();
    Timer(double timer);
    ~Timer();

    void Update(double deltaTime);
    void Reset();

    double GetCount();
    double GetProgress();

    operator bool() const;

private:
    bool m_value;
    double m_timer;
    double m_counter;
};

#endif // TIMER_H