#ifndef TIMING_H
#define TIMING_H

#include "Core.hpp"

class Timing
{
public:
    Timing();
    ~Timing();

    void Init();
    void Update();

    void Pause();
    void Unpause();

    double DeltaTime();
    double PausedTime();

private:
    Uint64 m_lastFrame;
    Uint64 m_currentFrame;
    double m_deltaTime;

    bool m_paused;
    double m_pausedTime;

    double GetFrameTime();
};

#endif // TIMING_H