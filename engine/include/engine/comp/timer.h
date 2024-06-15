#pragma once

#include <engine/comp/_component.h>
#include <engine/comp/script.h>

class TimerComponent : public Component {
private:
    Script _onTimerEnd;
public:
    int timeRemaining = -1;

    explicit TimerComponent(Script onTimerEnd);

    void operator()(Entity& self);
};
