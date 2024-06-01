#include "_system.hpp"


bool System::operator<(const System &other) const {
    return executionPriority < other.executionPriority;
}

/**
 * @brief Construct a new System:: System object
 *
 * @param executionPriority The priority of the system
 * @return
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
