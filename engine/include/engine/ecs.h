#pragma once

#include <engine/entity.h>
#include <engine/systems/_system.h>
#include <memory>
#include <set>

class ECS {
    static std::multiset<std::unique_ptr<Entity>> _entities;
    static std::set<std::unique_ptr<System>> _systems;
    static bool _isRunning;

    /**
     * @brief Adds a system to the ECS
     * @tparam SystemType
     */
    template <typename SystemType>
    static void AddSystem() {
        _systems.insert(std::make_unique<SystemType>());
    }
public:
    /**
     * @brief Adds an entity to the ECS
     * @tparam EntityType
     * @tparam Args
     * @param args
     */
    template <typename EntityType, typename... Args>
    static void AddEntity(Args&&... args) {
        _entities.insert(std::make_unique<EntityType>());
    }

    static std::multiset<std::unique_ptr<Entity>>& GetEntities();

    static void GameLoop();

    /**
     * @brief Stops the game loop
     */
    static void StopGame();
};


