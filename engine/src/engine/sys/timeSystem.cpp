#include <engine/sys/timeSystem.h>
#include <thread>

// Set static variables
std::chrono::time_point<std::chrono::steady_clock> TimeSystem::_frameStart;
std::chrono::milliseconds TimeSystem::_frameRate = std::chrono::milliseconds(1000 / 60);

void TimeSystem::FrameStart() {
    _frameStart = std::chrono::high_resolution_clock::now();
}

void TimeSystem::FrameEnd() {
    // Sleep for the remaining time
    std::this_thread::sleep_until(_frameStart + _frameRate);
}

void TimeSystem::SetFrameRate(std::chrono::milliseconds frameRate) {
    TimeSystem::_frameRate = frameRate;
}
