#pragma once

#include "../entities/_entity.h"

/**
 * @brief Base class for all systems
 */
class System {
public:
    // It is important to have a virtual destructor
    virtual ~System() = default;

    /**
     * @brief Runs the system on an entity
     * @details This function gets called by the ECS class every frame
     * and is called for every entity in the ECS.
     * @note This function should be overwritten by the child systems.
     * @param entity
     */
    virtual void UpdateEntity(Entity &entity) = 0;

    // Runs before looping over entities
    virtual void PreUpdate() {}

    // Runs after looping over entities
    virtual void PostUpdate() {}
};
