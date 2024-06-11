#pragma once

#include <engine/entity.h>
#include <engine/sys/renderSystem.h>
#include <memory>
#include <set>

class ECS {
    static std::multiset<std::unique_ptr<Entity>> _entities;
    static bool _isRunning;
    static RenderSystem _renderSystem;
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


