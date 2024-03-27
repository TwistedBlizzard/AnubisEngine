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

    double DeltaTime();

private:
    Uint64 m_lastFrame;
    Uint64 m_currentFrame;
    double m_deltaTime;
};

#endif // TIMING_H