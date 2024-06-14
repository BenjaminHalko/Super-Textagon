#pragma once

#include <engine/entity.h>
#include <engine/sys/renderSystem.h>
#include <memory>
#include <set>

class Engine {
    static std::multiset<std::unique_ptr<Entity>> _entities;
    static bool _isRunning;
    static RenderSystem _renderSystem;
public:
    /**
     * @brief Adds an entity to the Engine
     * @tparam Args
     */
    template <typename... Args>
    static Entity& AddEntity(Args&&... args) {
        _entities.insert(std::make_unique<Entity>(std::forward<Args>(args)...));
        return *_entities.begin()->get();
    }

    /**
     * @brief Gets all entities
     */
    static std::multiset<std::unique_ptr<Entity>>& GetEntities();

    /**
     * @brief Starts the game loop
     */
    static void GameLoop();

    /**
     * @brief Stops the game loop
     */
    static void StopGame();
};


