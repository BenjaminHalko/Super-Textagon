#pragma once

#include <engine/systems/_system.h>
#include <engine/components/spriteComponent.h>

class SpriteSystem : public System {
public:
    static SpriteComponent GenerateShape(
        float radius,
        int numSides,
        Color innerColor,
        float innerAlpha,
        Color outerColor,
        float outerAlpha
    );
};