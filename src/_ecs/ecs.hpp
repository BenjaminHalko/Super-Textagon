#pragma once

#include "../entities/_entity.hpp"
#include "../systems/_system.hpp"
#include <memory>
#include <set>

class ECS {
    std::multiset<std::unique_ptr<Entity>> entities;
    std::set<std::unique_ptr<System>> systems;
public:
    template <typename EntityType, typename... Args>
    void AddEntity(Args&&... args) {
        entities.insert(std::make_unique<EntityType>());
    }

    template <typename SystemType>
    void AddSystem() {
        systems.insert(std::make_unique<SystemType>());
    }

    void Step();
};

//std::multiset<std::unique_ptr<Entity>> ECS::entities;
//std::set<std::unique_ptr<System>> ECS::systems;
