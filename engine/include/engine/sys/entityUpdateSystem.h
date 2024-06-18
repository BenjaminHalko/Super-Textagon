#pragma once

#include <engine/sys/_system.h>

/**
 * @brief A system that handles updating entities.
 */
class EntityUpdateSystem : public System {
    friend class Engine;

    /**
     * @brief Updates all entities in the system.
     */
    static void Update();
};