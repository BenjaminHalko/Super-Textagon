#include "_entity.h"

/**
 * @brief Check if the entity uses a system
 * @param systemType The type of the system
 * @return bool True if the entity uses the system
 */
bool Entity::UsesSystem(std::type_index system) const {
    return std::find(systemsToUse.begin(), systemsToUse.end(), system) != systemsToUse.end();
}

// Orders the entity inside of sets
bool Entity::operator<(const Entity &other) const {
    return executionPriority < other.executionPriority;
}

// Check if the entity is destroyed
bool Entity::gotDestroyed() const {
    return destroyed;
}
