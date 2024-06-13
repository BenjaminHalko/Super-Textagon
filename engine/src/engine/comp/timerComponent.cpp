#include <engine/comp/timerComponent.h>
#include <algorithm>

TimerComponent::TimerComponent(ScriptComponent onTimerEnd) : _onTimerEnd(onTimerEnd) {}

void TimerComponent::operator()() {
    _onTimerEnd();
}
