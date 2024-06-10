#pragma once

#include <engine/sys/_system.h>
#include <engine/comp/spriteComponent.h>

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
