#pragma once

#include <engine/comp/_component.h>
#include <engine/comp/script.h>

/**
 * @brief A component that represents a timer.
 * @details This manages a timer and executes a script when the timer ends.
 */
class TimerComponent : public Component {
private:
    Script _onTimerEnd;
public:
    int timeRemaining = -1; // Time remaining for the timer, default is -1 (inactive).

    /**
     * @brief Constructs a TimerComponent with the given script.
     *
     * @param onTimerEnd The script to execute when the timer ends.
     */
    explicit TimerComponent(Script onTimerEnd);

    /**
     * @brief Executes the script when the timer ends.
     *
     * @param self Reference to the entity on which the script is executed.
     */
    void operator()(Entity& self);
};