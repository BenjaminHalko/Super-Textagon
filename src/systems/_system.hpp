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
     * @details The first element of the pair is the function to be called, the second element is the priority of the callback
     */
    std::vector<std::pair<void(*)(), int>> callbacks;
public:
    virtual ~System() = default;
    virtual void StepEntity(Entity& entity) = 0;

    bool operator<(const System &other) const;
    void Step(std::multiset<std::unique_ptr<Entity>> &entities);
};
