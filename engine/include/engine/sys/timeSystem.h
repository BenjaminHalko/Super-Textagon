#pragma once

#include <engine/sys/_system.h>

#include <chrono>

class TimeSystem : public System {
    friend class Engine;
    static const std::chrono::time_point<std::chrono::steady_clock> _engineStart;
    static std::chrono::time_point<std::chrono::steady_clock> _frameStart;
    static std::chrono::milliseconds _frameRate;
    static float _deltaTime;
    static float _timeRunning;
    static void FrameStart();
    static void FrameEnd();
public:
    static void SetFrameRate(std::chrono::milliseconds frameRate);
    static float DeltaTime();
    static float TimeRunning();
};
