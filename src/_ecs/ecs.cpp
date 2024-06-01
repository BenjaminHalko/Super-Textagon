#include "ecs.hpp"

std::multiset<std::unique_ptr<Entity>> ECS::entities;
std::set<std::unique_ptr<System>> ECS::systems;

/**
 * @brief Runs the system's code on every frame
 */
void ECS::Step() {
    for (auto &system : systems) {
        system->Step(entities);
    }

    for (auto it = entities.begin(); it != entities.end();) {
        if ((*it)->gotDestroyed()) {
            it = entities.erase(it);
        } else {
            ++it;
        }
    }
}
