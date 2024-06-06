#pragma once

#include "_entity.h"
#include "../components/spriteComponent.h"
#include "../systems/renderSystem.h"

/**
 * @brief A test entity
 */
class TestEntity : public Entity {
    SystemSet systemsToUse = {typeid(RenderSystem)};
public:
    TestEntity() {
        AddComponent<SpriteComponent>(0.25f, 6, 0, 1);
    }
};
