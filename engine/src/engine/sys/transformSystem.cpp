#include <engine/sys/transformSystem.h>
#include <cmath>

void TransformSystem::TranslatePoint(Point &point, float x, float y) {
    point.x += x;
    point.y += y;
}

void TransformSystem::RotatePoint(Point& point, float angle) {
    angle *= PI / 180;

    auto original = point;

    point.x = original.x * cosf(angle) - original.y * sinf(angle);
    point.y = original.x * sinf(angle) + original.y * cosf(angle);
}

void TransformSystem::ScalePoint(Point &point, float x_scale, float y_scale) {
    point.x *= x_scale;
    point.y *= y_scale;
}

void TransformSystem::ApplyTransformation(Point &point, TransformComponent &transform) {
    ScalePoint(point, transform.x_scale, transform.y_scale);
    RotatePoint(point, transform.rotation);
    TranslatePoint(point, transform.x, transform.y);
}

SpriteComponent TransformSystem::TransformSprite(SpriteComponent &sprite, TransformComponent &transform) {
    SpriteComponent newSprite;
    for (auto &point: sprite) {
        ColoredPoint newPoint = point;
        ApplyTransformation(newPoint.point, transform);
        newSprite.AddPoint(newPoint);
    }
    return newSprite;
}
