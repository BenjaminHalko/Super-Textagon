#pragma once

#include <chrono>

class Global {
public:
    static bool beatPulse;
    static std::chrono::time_point<std::chrono::steady_clock> roundStart;
    static float hue;
    static float zoom;
};
