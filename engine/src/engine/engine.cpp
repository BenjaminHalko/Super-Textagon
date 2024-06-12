#include <engine/engine.h>
#include <engine/sys/timeSystem.h>
#include <engine/sys/input.h>
#include <engine/sys/audioSystem.h>

// We need to define the static variables here
std::multiset<std::unique_ptr<Entity>> Engine::_entities;
bool Engine::_isRunning = true;
RenderSystem Engine::_renderSystem;

/**
 * @brief Gets the entities
 */
std::multiset<std::unique_ptr<Entity>>& Engine::GetEntities() {
    return _entities;
}

void Engine::GameLoop() {
    AudioSystem::Init();

    while(_isRunning) {
        TimeSystem::FrameStart();

        Input::Update();
        AudioSystem::Update();
        EntityUpdateSystem::Update();
        _renderSystem.Update();

        TimeSystem::FrameEnd();

        // TEMP
        if (Input::GetKeyPressed(Key::QUIT))
            StopGame();
    }

    AudioSystem::Clean();
}

void Engine::StopGame() {
    _isRunning = false;
}
