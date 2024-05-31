#pragma once

#include "entities/_entity.hpp"
#include "systems/_system.hpp"
#include <map>
#include <typeindex>
#include <vector>

class ECS {
    static std::vector<std::unique_ptr<Entity>> entities;
    static std::vector<std::unique_ptr<System>> systems;
public:
    template <typename EntityType, typename... Args>
    static void AddEntity(Args&&... args) {
        entities.push_back(std::make_unique<EntityType>(std::forward<Args>(args)...));
    }

    template <typename SystemType>
    static void AddSystem() {
        systems.push_back(std::make_unique<SystemType>());
    }

    static void Step() {
        for (auto &system : systems) {
            system->StepBegin();
            for(auto entity = entities.begin(); entity != entities.end();) {
                if ((*entity)->getDestroyed()) {
                    entity = entities.erase(entity);
                } else {
                    system->Step(**entity);
                    ++entity;
                }
            }
            system->StepEnd();
        }
    }
};

std::vector<std::unique_ptr<Entity>> ECS::entities;
std::vector<std::unique_ptr<System>> ECS::systems;
