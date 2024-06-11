#include <engine/sys/entityUpdateSystem.h>
#include <engine/engine.h>

void EntityUpdateSystem::Update() {
    for (auto& entity : Engine::GetEntities()) {
        // Run the update function of the entity
        entity->Update();

        // Update the timers of the entity
        for (auto &timer: entity->GetTimers()) {
            if (timer->timeRemaining > 0) {
                if (--timer->timeRemaining == 0) {
                    (*timer)();
                }
            }
        }
    }
}
