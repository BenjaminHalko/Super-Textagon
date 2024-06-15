#include <engine/engine.h>
#include <engine/sys/timeSystem.h>
#include <engine/sys/input.h>
#include <engine/sys/audioSystem.h>
#include <engine/sys/entityUpdateSystem.h>
#include "engine/comp/transform.h"

// We need to define the static variables here
std::multiset<std::unique_ptr<Entity>> Engine::_entities;
bool Engine::_isRunning = true;
RenderSystem Engine::_renderSystem;

std::vector<Entity*> Engine::GetEntities(std::string name) {
    std::vector<Entity*> entities;
    for (auto& entity : _entities) {
        if (entity->GetName() == name) {
            entities.push_back(entity.get());
        }
    }
    return entities;
}

void Engine::GameLoop() {
    Input::Init();
    AudioSystem::Init();

    while(_isRunning) {
        TimeSystem::FrameStart();

        Input::Update();
        AudioSystem::Update();
        EntityUpdateSystem::Update();
        _renderSystem.Update();

        TimeSystem::FrameEnd();

        // TEMP
        if (Input::GetKeyPressed(VK_ESCAPE))
            StopGame();
    }

    Input::Clean();
    AudioSystem::Clean();
}

void Engine::StopGame() {
    _isRunning = false;
}
