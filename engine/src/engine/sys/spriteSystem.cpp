#include <engine/sys/spriteSystem.h>
#include <cmath>

std::vector<ColoredPoint> SpriteSystem::GenerateShape(
        float radius,
        int numSides,
        Color innerColor,
        float innerAlpha,
        Color outerColor,
        float outerAlpha
) {
    std::vector<ColoredPoint> sprite;
    for (int i = 0; i < numSides; i++) {
        float angle = 2 * PI * (float) i / (float) numSides;
        sprite.push_back({{radius * cosf(angle), radius * sinf(angle)}, outerColor, outerAlpha});
        angle = 2 * PI * (float) (i + 1) / (float) numSides;
        sprite.push_back({{radius * cosf(angle), radius * sinf(angle)}, outerColor, outerAlpha});
        sprite.push_back({{0, 0}, innerColor, innerAlpha});
    }
    return sprite;
}
