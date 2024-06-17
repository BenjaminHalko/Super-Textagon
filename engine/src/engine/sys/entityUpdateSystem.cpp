#include <engine/sys/entityUpdateSystem.h>
#include <engine/engine.h>
#include <engine/comp/script.h>

void EntityUpdateSystem::Update() {
    for (auto entity: Engine::GetEntities<Script>()) {
        entity->GetComponent<Script>()(*entity);
    }
}
