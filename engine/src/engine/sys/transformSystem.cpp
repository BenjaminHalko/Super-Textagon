#include <engine/sys/transformSystem.h>
#include <cmath>

void TransformSystem::TranslatePoint(Point &point, float x, float y) {
    point.x += x;
    point.y += y;
}

void TransformSystem::ScalePoint(Point &point, float x_scale, float y_scale) {
    point.x *= x_scale;
    point.y *= y_scale;
}

void TransformSystem::RotatePoint(Point &point, float angle) {
    angle *= PI / 180;

    //angle = 90 * PI / 180;

    point.x = point.x * cosf(angle) - point.y * sinf(angle);
    point.y = point.x * sinf(angle) + point.y * cosf(angle);
}

void TransformSystem::ApplyTransformation(Point &point, TransformComponent &transform) {
    TranslatePoint(point, transform.x, transform.y);
    ScalePoint(point, transform.x_scale, transform.y_scale);
    RotatePoint(point, transform.rotation);
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
