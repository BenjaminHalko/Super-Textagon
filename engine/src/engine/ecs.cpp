#include <engine/ecs.h>
#include <engine/sys/timeSystem.h>
#include <engine/sys/input.h>

// We need to define the static variables here
std::multiset<std::unique_ptr<Entity>> ECS::_entities;
bool ECS::_isRunning = true;
RenderSystem ECS::_renderSystem;

/**
 * @brief Gets the entities
 */
std::multiset<std::unique_ptr<Entity>>& ECS::GetEntities() {
    return _entities;
}

void ECS::GameLoop() {
    while(_isRunning) {
        TimeSystem::FrameStart();

        Input::Update();
        _renderSystem.Update();

        TimeSystem::FrameEnd();


        // TEMP
        if (Input::GetKeyPressed(Key::QUIT))
            StopGame();
    }
}

void ECS::StopGame() {
    _isRunning = false;
}
