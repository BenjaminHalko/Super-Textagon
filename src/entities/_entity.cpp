#include "_entity.h"

// Orders the entity inside of sets
bool Entity::operator<(const Entity &other) const {
    return executionPriority < other.executionPriority;
}

// Check if the entity is destroyed
bool Entity::gotDestroyed() const {
    return destroyed;
}
