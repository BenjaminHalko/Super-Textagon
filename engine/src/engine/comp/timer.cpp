#include <engine/comp/timer.h>
#include <algorithm>

TimerComponent::TimerComponent(Script onTimerEnd) : _onTimerEnd(onTimerEnd) {}

void TimerComponent::operator()(Entity& self) {
    _onTimerEnd(self);
}
