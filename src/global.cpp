#include "global.h"

bool Global::beatPulse = false;
std::chrono::time_point<std::chrono::steady_clock> Global::roundStart = std::chrono::steady_clock::now();
float Global::hue = 0.0f;
float Global::zoom = 0;
