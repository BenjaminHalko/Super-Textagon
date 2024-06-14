#include "testEntity.h"
#include "engine/engine.h"
#include "engine/sys/audioSystem.h"
#include <engine/sys/collisionSystem.h>
#include <engine/sys/timeSystem.h>
#include <engine/comp/transform.h>
#include <engine/comp/sprite.h>
#include <engine/sys/input.h>
#include <cmath>

Entity& CreateTestEntity() {
    return Engine::AddEntity(
        Transform(0.5f, 0.5f),
        Sprite(0.2f, 3, 0xFFFFFF, 1, 0xFF0000, 0.5f)
    );
}


/*
void Update(Entity& entity) {
 CreateTestEntity();
    // Get the transform component
    auto& transform = GetComponent<TransformComponent>();

    // Rotate the entity by 1 degree per frame

    transform.x = 0.5f + 0.25f * cosf((float)TimeSystem::TimeRunning() + _offset * 2);

    //transform.y = 0.5f + 0.1f * sinf((float)TimeSystem::TimeRunning() + _offset * 2);

    if (_offset == 0) {
        auto entity = (Engine::GetEntities().begin())->get();
        if (CollisionSystem::CheckCollision(*this, *entity)) {
            GetComponent<SpriteComponent>()[0].color = 0x00FF00;
           
        } else {
            GetComponent<SpriteComponent>()[0].color = 0xFFFF00;
        }
    }

    if (Input::GetKeyPressed(Key::RIGHT) && _offset == 0) {
        AudioSystem::PlayAudio("audio/explode.wav", false, 0.04f);
    }
}
 */
