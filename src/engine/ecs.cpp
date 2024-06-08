#include "ecs.h"
#include "systems/timeSystem.h"

// We need to define the static variables here
std::multiset<std::unique_ptr<Entity>> ECS::_entities;
std::set<std::unique_ptr<System>> ECS::_systems;
bool ECS::_isRunning = true;

/**
 * @brief Gets the entities
 */
std::multiset<std::unique_ptr<Entity>>& ECS::GetEntities() {
    return _entities;
}

/**
 * @brief Runs the every frame
 * @details It loops over all the systems and calls their UpdateEntity function
 */
void ECS::GameLoop() {
    while(_isRunning) {
        TimeSystem::FrameStart();
        for(auto& system : _systems) {
            system->Update();
        }
        TimeSystem::FrameEnd();
    }
}

/**
 * @brief Stops the game loop
 */
void ECS::StopGame() {
    _isRunning = false;
}
