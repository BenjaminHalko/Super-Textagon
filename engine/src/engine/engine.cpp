#include <engine/engine.h>
#include <engine/comp/depth.h>
#include <engine/comp/tag.h>
#include <engine/sys/timeSystem.h>
#include <engine/sys/input.h>
#include <engine/sys/audioSystem.h>
#include <engine/sys/entityUpdateSystem.h>

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

void Engine::GameLoop() {
    Input::Init();
    AudioSystem::Init();
    RenderSystem::Init();

    while(_isRunning) {
        TimeSystem::FrameStart();

        Input::Update();
        AudioSystem::Update();
        EntityUpdateSystem::Update();
        RenderSystem::Update();

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
