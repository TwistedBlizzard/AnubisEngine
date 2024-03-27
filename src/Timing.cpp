#include "Timing.hpp"

Timing::Timing():
m_lastFrame(0),
m_currentFrame(0),
m_deltaTime(0)
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
    m_deltaTime = double(m_currentFrame - m_lastFrame) / SDL_GetPerformanceFrequency();
}

double Timing::DeltaTime()
{
    return m_deltaTime;
}
