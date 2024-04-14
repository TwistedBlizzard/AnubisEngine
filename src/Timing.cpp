#include "Timing.hpp"

Timing::Timing():
m_lastFrame(0),
m_currentFrame(0),
m_deltaTime(0),
m_paused(false)
{}

Timing::~Timing()
{}

void Timing::Init()
{
    m_currentFrame = SDL_GetPerformanceCounter();
}

void Timing::Update()
{
    m_lastFrame = m_currentFrame;
    m_currentFrame = SDL_GetPerformanceCounter();

    if (m_paused)
    {
        m_pausedTime = GetFrameTime();
        return;
    }

    m_deltaTime = GetFrameTime();
}

void Timing::Pause()
{
    m_paused = true;
    m_deltaTime = 0.0;
}

void Timing::Unpause()
{
    m_paused = false;
    m_deltaTime = GetFrameTime();
    m_pausedTime = 0.0;
}

double Timing::DeltaTime()
{
    return m_deltaTime;
}

double Timing::PausedTime()
{
    return m_pausedTime;
}

double Timing::GetFrameTime()
{
    return double(m_currentFrame - m_lastFrame) / SDL_GetPerformanceFrequency();
}
