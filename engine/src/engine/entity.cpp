#include <engine/entity.h>

TimerComponent& Entity::AddTimer(ScriptComponent script) {
    timers.push_back(std::make_unique<TimerComponent>(script));
    return *timers.back();
}

std::vector<std::unique_ptr<TimerComponent>>& Entity::GetTimers() {
    return timers;
}

bool Entity::operator<(const Entity &other) const {
    return depth < other.depth;
}

void Entity::Destroy() {
    destroyed = true;
}

bool Entity::gotDestroyed() const {
    return destroyed;
}
