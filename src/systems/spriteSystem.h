#pragma once

#include "_system.h"
#include "../components/spriteComponent.h"

class SpriteSystem : public System {
public:
    static SpriteComponent GenerateShape(float radius, int numSides, float innerLuminance, float outerLuminance, Color innerColor, Color outerColor);
};
