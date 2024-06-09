#include <engine/systems/spriteSystem.h>

SpriteComponent SpriteSystem::GenerateShape(
    float radius,
    int numSides,
    Color innerColor,
    float innerAlpha,
    Color outerColor,
    float outerAlpha
) {
    SpriteComponent sprite;
    for (int i = 0; i < numSides; i++) {
        float angle = 2 * 3.14f * (float)i / (float)numSides;
        sprite.AddPoint({{radius * cosf(angle), radius * sinf(angle)}, outerColor, outerAlpha});
        angle = 2 * 3.14f * (float)(i + 1) / (float)numSides;
        sprite.AddPoint({{radius * cosf(angle), radius * sinf(angle)}, outerColor, outerAlpha});
        sprite.AddPoint({{0, 0}, innerColor, innerAlpha});
    }
    return sprite;
}
