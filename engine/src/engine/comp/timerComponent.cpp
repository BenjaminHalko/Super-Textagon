#include <engine/comp/timerComponent.h>
#include <algorithm>

TimerComponent::TimerComponent(ScriptComponent onTimerEnd) : _onTimerEnd(onTimerEnd) {}

//void TimerComponent::Start(int time) {
    //t/imeRemaining = time;
    //totalTime = time;
//}

void TimerComponent::operator()() {
    _onTimerEnd();
}
