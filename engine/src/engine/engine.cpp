#include <engine/engine.h>
#include <engine/comp/depth.h>
#include <engine/comp/tag.h>
#include <engine/sys/timeSystem.h>
#include <engine/sys/input.h>
#include <engine/sys/audioSystem.h>
#include <engine/sys/entityUpdateSystem.h>
#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

// We need to define the static variables here
std::vector<std::unique_ptr<Entity>> Engine::_entities;
bool Engine::_isRunning = true;

bool Engine::CompareEntityDepth(const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b) {
    return a->GetComponent<Depth>().Get() > b->GetComponent<Depth>().Get();
}

std::vector<Entity*> Engine::GetEntities(std::string tag) {
    std::vector<Entity*> entities;
    for (auto entity : GetEntities<Tag>()) {
        if (entity->GetComponent<Tag>().Get() == tag) {
            entities.push_back(entity);
        }
    }
    return entities;
}

void Engine::RemoveDeletedEntities() {
    _entities.erase(
        std::remove_if(_entities.begin(), _entities.end(), [](const std::unique_ptr<Entity>& entity) {
            return entity->IsDeleted();
        }),
        _entities.end()
    );
}

void Engine::GameLoop() {
    TimeSystem::FrameStart();

    Input::Update();
    AudioSystem::Update();
    EntityUpdateSystem::Update();
    RemoveDeletedEntities();
    RenderSystem::Update();

    TimeSystem::FrameEnd();

#ifdef EMSCRIPTEN
    if (!_isRunning)
        emscripten_cancel_main_loop();
#endif
}

void Engine::RunGame() {
    // Init
    Input::Init();
    AudioSystem::Init();
    RenderSystem::Init();

    // Game loop
#ifndef EMSCRIPTEN
    while (_isRunning)
        GameLoop();
#else
    emscripten_set_main_loop(GameLoop, 0, 1);
#endif

    // Clean
    Input::Clean();
    AudioSystem::Clean();
}

void Engine::StopGame() {
    _isRunning = false;
}
