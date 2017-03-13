#pragma once
#include <cstdint>
#include <cstddef>
class Timer {
public:
    Timer();
    void Start();
    void Stop();
    void Pause();
    void Resume();
    uint32_t GetTicks();

    bool isStarted();
    bool isPaused();

private:
    uint32_t start_ticks;
    uint32_t paused_ticks;

    bool paused;
    bool started;
};
