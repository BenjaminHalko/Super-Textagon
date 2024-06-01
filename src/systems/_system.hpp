#pragma once

#include "../entities/_entity.hpp"
#include <vector>
#include <set>
#include <memory>

/**
 * @brief Base class for all systems
 */
class System {
    // Execution priority of the system
    int executionPriority = 0;

    /**
     * @brief Callbacks to be called through out the Step function
     * @details The first element of the pair is the function to be called,
     * the second element is the priority of the callback
     */
    std::vector<std::pair<void (*)(), int>> callbacks;
public:
    virtual ~System() = default;
    void Step(std::multiset<std::unique_ptr<Entity>> &entities);
    bool operator<(const System &other) const;

    /**
     * @brief Runs the system's code on every frame
     * @details This function is called by the ECS class
     * This function should be overwritten by the child systems
     * @param entities
     */
    virtual void StepEntity(Entity &entity) = 0;
};
