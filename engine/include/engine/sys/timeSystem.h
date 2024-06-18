#pragma once

#include <engine/sys/_system.h>
#include <chrono>

/**
 * @brief A system that handles time management in the engine.
 */
class TimeSystem : public System {
    friend class Engine;

    static const std::chrono::time_point<std::chrono::steady_clock> _engineStart;
    static std::chrono::time_point<std::chrono::steady_clock> _frameStart;
    static std::chrono::milliseconds _frameRate;
    static float _deltaTime;
    static float _timeRunning; 

    /**
     * @brief Marks the start of a new frame.
     */
    static void FrameStart();

    /**
     * @brief Marks the end of the current frame.
     */
    static void FrameEnd();
public:
    /**
     * @brief Sets the desired frame rate for the engine.
     *
     * @param frameRate The desired frame rate in milliseconds.
     */
    static void SetFrameRate(std::chrono::milliseconds frameRate);

    /**
     * @brief Gets the time elapsed between the current and previous frames.
     *
     * @return The time elapsed between frames in seconds.
     */
    static float DeltaTime();

    /**
     * @brief Gets the total time the engine has been running.
     *
     * @return The total running time in seconds.
     */
    static float TimeRunning();
};