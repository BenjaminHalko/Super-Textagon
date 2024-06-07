#pragma once

#include "_system.h"
#include "../components/spriteComponent.h"

// THIS MIGHT BE ABLE TO BE JUST A FUNCTION AND NOT A SYSTEM

class SpriteSystem : public System {
public:
    static SpriteComponent GenerateShape(
        float radius,
        int numSides,
        Color innerColor,
        Color outerColor
    );
};
