#pragma once

#include <engine/entity.h>
#include <engine/sys/renderSystem.h>
#include <memory>
#include <set>

class Engine {
    static std::multiset<std::unique_ptr<Entity>> _entities;
    static bool _isRunning;
public:
    /**
     * @brief Adds an entity to the Engine
     * @tparam Args
     */
    template <typename... Args>
    static Entity& AddEntity(std::string name, int depth, Args&&... args) {
        auto entityPtr = std::make_unique<Entity>(std::move(name), depth, std::forward<Args>(args)...);
        auto entity = entityPtr.get();
        _entities.insert(std::move(entityPtr));
        return *entity;
    }

    /**
     * @brief Gets all the entities with a specific component
     */
    template <typename ... ComponentTypes>
    static std::vector<Entity*> GetEntities() {
        std::vector<Entity*> entities;
        for (auto& entity : _entities) {
            if (entity->HasComponents<ComponentTypes...>()) {
                entities.push_back(entity.get());
            }
        }
        return entities;
    }

    static std::vector<Entity*> GetEntities(std::string name);

    /**
     * @brief Starts the game loop
     */
    static void GameLoop();

    /**
     * @brief Stops the game loop
     */
    static void StopGame();
};


