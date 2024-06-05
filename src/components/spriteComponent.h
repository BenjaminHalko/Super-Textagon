#pragma once

#include "_component.h"

// These might need their own file :/
#define TriangleStrip std::vector<Point>
#define PI 3.14159265358979323846f

struct Point {
    float x, y;
};

/**
 * @brief This component is used to store the sprite of an entity
 * @details You pass a set of coordinates to the constructor
 */
class SpriteComponent : public Component {
    TriangleStrip sprite;

    static Point rotateVector(Point &point, float angle) {
        angle *= PI / 180;
        return {
            point.x * cosf(angle) - point.y * sinf(angle),
            point.x * sinf(angle) + point.y * cosf(angle)
        };
    }
public:
    explicit SpriteComponent(TriangleStrip sprite) : sprite(std::move(sprite)) {}
    explicit SpriteComponent(float radius, int numSides) {
        for (int i = 0; i < numSides; i++) {
            float angle = 2 * PI * (float)i / (float)numSides;
            sprite.push_back({radius * cosf(angle), radius * sinf(angle)});
        }
    }

    float scale = 1;
    float rotation = 0;

    TriangleStrip GetSprite(float x, float y) {
        TriangleStrip transformedSprite(sprite.size());
        for (int i = 0; i < sprite.size(); i++) {
            transformedSprite[i] = {
                sprite[i].x * scale,
                sprite[i].y * scale
            };
            transformedSprite[i] = rotateVector(transformedSprite[i], rotation);
            transformedSprite[i].x += x;
            transformedSprite[i].y += y;
        }
        return transformedSprite;
    }
};
