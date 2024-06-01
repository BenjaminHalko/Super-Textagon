#include "ecs.hpp"

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
