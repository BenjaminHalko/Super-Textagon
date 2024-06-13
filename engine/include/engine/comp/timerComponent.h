#pragma once

#include <engine/comp/_component.h>
#include <engine/comp/scriptComponent.h>

class TimerComponent : public Component {
private:
    ScriptComponent _onTimerEnd;
public:
    int timeRemaining = -1;

    explicit TimerComponent(ScriptComponent onTimerEnd);

    void operator()();
};
