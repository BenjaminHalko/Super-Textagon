#include <engine/entity.h>

bool Entity::operator<(const Entity &other) const {
    return executionPriority < other.executionPriority;
}

bool Entity::gotDestroyed() const {
    return destroyed;
}
