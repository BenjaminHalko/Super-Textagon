#pragma once

#include "_component.h"
#include <vector>

// These might need their own file :/
#define TriangleList std::vector<Point>
#define Color unsigned short
#define PI 3.14159265358979323846f

struct Point {
    float x, y, luminance;
    Color color;
};

/**
 * @brief This component is used to store the sprite of an entity
 * @details You pass a set of coordinates to the constructor
 */
class SpriteComponent : public Component {
    TriangleList sprite;
    static Point RotateVector(Point &point, float angle);
public:
    float scale = 1;
    float rotation = 0;

    explicit SpriteComponent(TriangleList sprite) : sprite(std::move(sprite)){}
    static TriangleList GenerateShape(float radius, int numSides, float innerLuminance, float outerLuminance, Color innerColor, Color outerColor);
    TriangleList GetSprite(float x, float y);
};
