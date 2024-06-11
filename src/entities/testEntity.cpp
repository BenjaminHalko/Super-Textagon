#include "testEntity.h"
#include <engine/sys/spriteSystem.h>
#include <engine/comp/transformComponent.h>
#include <engine/comp/spriteComponent.h>

TestEntity::TestEntity() {
    // Create a transform component with a position of (0.5, 0.5)
    AddComponent<TransformComponent>(0.5f, 0.5f);

    // Create a triangle with a red outline and a white fill
    // With a radius of 0.25 (or quarter the screen width)
    AddComponent<SpriteComponent>(SpriteSystem::GenerateShape(0.25f, 3, 0xFFFFFF, 1, 0xFF0000, 0.5f));
}
