#include "_system.hpp"

/**
 * @brief Run code on every entity that uses this system
 * @details This function is called by the ECS class
 * This function should be overwritten by the child systems
 * @param entity
 */
void System::Step(std::multiset<std::unique_ptr<Entity>> &entities) {
    auto callbackIt = callbacks.begin();

    for (auto &entity : entities) {
        // Check if there are any callbacks to be called
        while (callbackIt != callbacks.end() && callbackIt->second < entity->getExecutionPriority()) {
            callbackIt->first();
            ++callbackIt;
        }

        // Check if the entity uses this system
        if (!entity->UsesSystem(typeid(*this)))
            continue;

        // Run the system on the entity
        StepEntity(*entity);
    }

    // Call the remaining callbacks
    while (callbackIt != callbacks.end()) {
        callbackIt->first();
        ++callbackIt;
    }
}

// Allows the systems to be sorted by their execution priority
bool System::operator<(const System &other) const {
    return executionPriority < other.executionPriority;
}
