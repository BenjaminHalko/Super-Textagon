#include <iostream>
#include "ecs.h"

// We need to define the static variables here
std::multiset<std::unique_ptr<Entity>> ECS::entities;
std::set<std::unique_ptr<System>> ECS::systems;

/**
 * @brief Runs the every frame
 * @details It loops over all the systems and calls their UpdateEntity function
 */
void ECS::Update() {
    for (auto& system : systems) {
        system->PreUpdate();

        // Loop over all the entities
        for(auto entity = entities.begin(); entity != entities.end(); entity++) {
            if (!(*entity)->UsesSystem(typeid(*(system.get())))) {
                continue;
            }

            // Update the entity
            system->UpdateEntity(**entity);

            // Check if the entity got destroyed
            // If it did, remove it from the set
            // and move the iterator back one step
            if ((*entity)->gotDestroyed())
                entity = std::prev(entities.erase(entity));
        }

        system->PostUpdate();
    }
}
