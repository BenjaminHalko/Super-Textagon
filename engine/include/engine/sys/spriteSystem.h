#pragma once

#include <engine/sys/_system.h>
#include <engine/comp/spriteComponent.h>

class SpriteSystem : public System {
public:
    static std::vector<ColoredPoint> GenerateShape(
        float radius,
        int numSides,
        Color innerColor,
        float innerAlpha,
        Color outerColor,
        float outerAlpha
    );
};
