#pragma once

#include <chrono>

#define BaseWallSpd 0.01f
#define BasePlayerSpd 12

class Global {
public:
    static bool beatPulse;
    static float hue;
    static float zoom;
    static std::chrono::time_point<std::chrono::steady_clock> roundStart;
    static float gameSpeed;
};
