#pragma once

#include "_entity.h"
#include "../components/spriteComponent.h"
#include "../systems/renderSystem.h"

/**
 * @brief A test entity
 */
class TestEntity : public Entity {
public:
    TestEntity() {
        systemsToUse.emplace_back(typeid(RenderSystem));
        AddComponent<SpriteComponent>(SpriteComponent::GenerateShape(0.25f, 6, 0.5f, 1, 0x00FFFF, 0x00FF33));
    }
};
