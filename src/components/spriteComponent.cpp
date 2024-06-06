#include "spriteComponent.h"

Point SpriteComponent::RotateVector(Point &point, float angle) {
    angle *= PI / 180;
    return {
        point.x * cosf(angle) - point.y * sinf(angle),
        point.x * sinf(angle) + point.y * cosf(angle),
        point.luminance,
        point.color
    };
}

TriangleList SpriteComponent::GenerateShape(float radius, int numSides, float innerLuminance, float outerLuminance, Color innerColor, Color outerColor) {
    TriangleList shape;
    for (int i = 0; i < numSides; i++) {
        float angle = 2 * PI * (float)i / (float)numSides;
        shape.push_back({radius * cosf(angle), radius * sinf(angle), outerLuminance, outerColor});
        angle = 2 * PI * (float)(i + 1) / (float)numSides;
        shape.push_back({radius * cosf(angle), radius * sinf(angle), outerLuminance, outerColor});
        shape.push_back({0, 0, innerLuminance, innerColor});
    }
    return shape;
}

TriangleList SpriteComponent::GetSprite(float x, float y) {
    TriangleList transformedSprite(sprite.size());
    for (int i = 0; i < sprite.size(); i++) {
        transformedSprite[i] = {
            sprite[i].x * scale,
            sprite[i].y * scale,
            sprite[i].luminance,
            sprite[i].color
        };
        transformedSprite[i] = RotateVector(transformedSprite[i], rotation);
        transformedSprite[i].x += x;
        transformedSprite[i].y += y;
    }
    return transformedSprite;
}
