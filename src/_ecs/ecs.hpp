#pragma once

#include "../entities/_entity.hpp"
#include "../systems/_system.hpp"
#include <memory>
#include <set>

class ECS {
    static std::multiset<std::unique_ptr<Entity>> entities;
    static std::set<std::unique_ptr<System>> systems;
public:
    /**
     * @brief Adds an entity to the ECS
     * @tparam EntityType
     * @tparam Args
     * @param args
     */
    template <typename EntityType, typename... Args>
    static void AddEntity(Args&&... args) {
        entities.insert(std::make_unique<EntityType>());
    }

    /**
     * @brief Adds a system to the ECS
     * @tparam SystemType
     */
    template <typename SystemType>
    static void AddSystem() {
        systems.insert(std::make_unique<SystemType>());
    }

    static void Step();
};


