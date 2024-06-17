#pragma once

#include <engine/entity.h>
#include <engine/sys/renderSystem.h>
#include <memory>
#include <set>

class Engine {
    static bool CompareEntityDepth(const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b);
    static std::vector<std::unique_ptr<Entity>> _entities;
    static bool _isRunning;
public:
    /**
     * @brief Adds an entity to the Engine
     * @tparam Args
     */
    template <typename... Args>
    static Entity& AddEntity(Args&&... args) {
        auto entityPtr = std::make_unique<Entity>(std::forward<Args>(args)...);
        auto entity = entityPtr.get();
        _entities.push_back(std::move(entityPtr));
        std::sort(_entities.begin(), _entities.end(), CompareEntityDepth);
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

    static std::vector<Entity*> GetEntities(std::string tag);

    /**
     * @brief Starts the game loop
     */
    static void GameLoop();

    /**
     * @brief Stops the game loop
     */
    static void StopGame();
};


