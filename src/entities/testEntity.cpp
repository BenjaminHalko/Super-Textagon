#include "testEntity.h"
#include "engine/engine.h"
#include <engine/sys/collisionSystem.h>
#include <engine/sys/timeSystem.h>
#include <engine/sys/spriteSystem.h>
#include <engine/comp/transformComponent.h>
#include <engine/comp/spriteComponent.h>

TestEntity::TestEntity(int offset) : _offset(offset) {
    // Create a transform component with a position of (0.5, 0.5)
    AddComponent<TransformComponent>(0.5f, 0.5f);

    // Create a triangle with a red outline and a white fill
    // With a radius of 0.25 (or quarter the screen width)
    auto sprite = AddComponent<SpriteComponent>(SpriteSystem::GenerateShape(0.2f, 3, 0xFFFFFF, 1, 0xFF0000, 0.5f));



    AddComponent<ColliderComponent>(sprite);
}

void TestEntity::Update() {
    // Get the transform component
    auto& transform = GetComponent<TransformComponent>();

    // Rotate the entity by 1 degree per frame

    transform.x = 0.5f + 0.25f * cosf((float)TimeSystem::FrameCount() / 10 + _offset * 2);

    if (_offset == 0) {
        auto entity = (Engine::GetEntities().begin())->get();
        if (CollisionSystem::CheckCollision(*this, *entity)) {
            GetComponent<SpriteComponent>()[0].color = 0x00FF00;
        } else {
            GetComponent<SpriteComponent>()[0].color = 0xFFFF00;
        }
    }
}
