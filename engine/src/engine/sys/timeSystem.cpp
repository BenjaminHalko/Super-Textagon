#include <engine/sys/timeSystem.h>
#include <thread>
#include <cmath>

// Set static variables
const std::chrono::time_point<std::chrono::steady_clock> TimeSystem::_engineStart = std::chrono::steady_clock::now();
std::chrono::time_point<std::chrono::steady_clock> TimeSystem::_frameStart;
std::chrono::milliseconds TimeSystem::_frameRate = std::chrono::milliseconds(1000 / 60);
float TimeSystem::_deltaTime = 0.0f;
float TimeSystem::_timeRunning = 0.0f;

void TimeSystem::FrameStart() {
    _timeRunning = std::chrono::duration<float>(std::chrono::steady_clock::now() - _engineStart).count();
    _deltaTime = std::chrono::duration<float>(std::chrono::steady_clock::now() - _frameStart).count();
    _deltaTime /= (float)_frameRate.count() / 1000.0f;
    _deltaTime = (float)fmin(_deltaTime, 1.0f);
    _frameStart = std::chrono::steady_clock::now();
}

void TimeSystem::FrameEnd() {
    // Sleep for the remaining time
    std::this_thread::sleep_until(_frameStart + _frameRate);
}

void TimeSystem::SetFrameRate(std::chrono::milliseconds frameRate) {
    TimeSystem::_frameRate = frameRate;
}

float TimeSystem::DeltaTime() {
    return _deltaTime;
}

float TimeSystem::TimeRunning() {
    return _timeRunning;
}
