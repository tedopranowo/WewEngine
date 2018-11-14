#pragma once

#include <chrono>

class Timer
{
    typedef std::chrono::high_resolution_clock Clock;

private:
    std::chrono::steady_clock::time_point m_startTime;

public:
    Timer() {}
    ~Timer() {}

    void Start();
    float GetDeltaTime() const;
};