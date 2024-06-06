#include "spriteSystem.h"

SpriteComponent SpriteSystem::GenerateShape(float radius, int numSides, float innerLuminance, float outerLuminance, Color innerColor, Color outerColor) {
    std::vector<Point> shape;
    for (int i = 0; i < numSides; i++) {
        float angle = 2 * PI * (float)i / (float)numSides;
        shape.push_back({radius * cosf(angle), radius * sinf(angle), outerLuminance, outerColor});
        angle = 2 * PI * (float)(i + 1) / (float)numSides;
        shape.push_back({radius * cosf(angle), radius * sinf(angle), outerLuminance, outerColor});
        shape.push_back({0, 0, innerLuminance, innerColor});
    }
    return SpriteComponent(shape);
}
