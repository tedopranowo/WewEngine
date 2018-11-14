#include "Timer.h"

void Timer::Start()
{
    m_startTime = Clock::now();
}

float Timer::GetDeltaTime() const
{
    std::chrono::duration<float> deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(Clock::now() - m_startTime); //seconds
    return deltaTime.count();
}
