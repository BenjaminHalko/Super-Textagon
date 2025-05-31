#include <engine/sys/transformSystem.h>
#include <cmath>

void TransformSystem::TranslatePoint(Vector2 &point, float x, float y) {
    point.x += x;
    point.y += y;
}

void TransformSystem::RotatePoint(Vector2& point, float angle) {
    angle *= PI / 180;

    auto original = point;

    point.x = original.x * cosf(angle) - original.y * sinf(angle);
    point.y = original.x * sinf(angle) + original.y * cosf(angle);
}

void TransformSystem::ScalePoint(Vector2 &point, float x_scale, float y_scale) {
    point.x *= x_scale;
    point.y *= y_scale;
}

void TransformSystem::ApplyTransformation(Vector2 &point, Transform &transform) {
    ScalePoint(point, transform.x_scale, transform.y_scale);
    RotatePoint(point, transform.rotation);
    TranslatePoint(point, transform.x, transform.y);
}

Sprite TransformSystem::TransformSprite(Sprite &sprite, Transform &transform) {
    Sprite newSprite;
    newSprite.tintAlpha = sprite.tintAlpha;
    newSprite.tint = sprite.tint;
    newSprite.alpha = sprite.alpha;
    for (auto &point: sprite) {
        ColoredPoint newPoint = point;
        ApplyTransformation(newPoint.point, transform);
        newSprite.AddPoint(newPoint);
    }
    return newSprite;
}

Collider TransformSystem::TransformCollider(Collider &collider, Transform &transform) {
    Collider newCollider;
    for (auto &point : collider) {
        Vector2 newPoint = point;
        ApplyTransformation(newPoint, transform);
        newCollider.AddPoint(newPoint);
    }
    return newCollider;
}
