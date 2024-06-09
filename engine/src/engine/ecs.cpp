#include <engine/ecs.h>
#include <engine/systems/timeSystem.h>

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

void ECS::GameLoop() {
    while(_isRunning) {
        TimeSystem::FrameStart();
        for(auto& system : _systems) {
            system->Update();
        }
        TimeSystem::FrameEnd();
    }
}

void ECS::StopGame() {
    _isRunning = false;
}
