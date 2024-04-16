#include "Timer.hpp"

Timer::Timer():
m_value(true),
m_timer(0.0),
m_counter(0.0)
{
}

Timer::Timer(double timer):
m_value(true),
m_timer(timer),
m_counter(0.0)
{
}

Timer::~Timer()
{
}

void Timer::Update(double deltaTime)
{
    // Check if we're already true
    if (m_value)
        return;

    // Assume that the countdown is running
    m_counter += deltaTime;

    // If our counter is up, set to true;
    if (m_counter >= m_timer)
        m_value = true;
}

void Timer::Reset()
{
    m_value = false;
    m_counter = 0.0;
}

double Timer::GetCount()
{
    return m_counter;
}

double Timer::GetProgress()
{
    return m_counter / m_timer;
}

Timer::operator bool() const
{
    return m_value;
}
