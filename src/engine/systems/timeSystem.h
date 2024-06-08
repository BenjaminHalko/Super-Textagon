#pragma once

#include "_system.h"

#include <chrono>

class TimeSystem : public System {
    static std::chrono::time_point<std::chrono::steady_clock>_frameStart;
    static std::chrono::milliseconds _frameRate;
public:
    static void FrameStart();
    static void FrameEnd();
    static void SetFrameRate(std::chrono::milliseconds frameRate);
};
