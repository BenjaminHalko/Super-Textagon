#include <engine/sys/_system.h>
#include <engine/common.h>
#include <engine/comp/transformComponent.h>
#include <engine/comp/spriteComponent.h>
#include <engine/comp/colliderComponent.h>

class TransformSystem : public System {
public:
    static void TranslatePoint(Point& point, float x, float y);
    static void ScalePoint(Point& point, float x_scale, float y_scale);
    static void RotatePoint(Point& point, float angle);
    static void ApplyTransformation(Point& point, TransformComponent& transform);
    static SpriteComponent TransformSprite(SpriteComponent& sprite, TransformComponent& transform);
    static ColliderComponent TransformCollider(ColliderComponent& collider, TransformComponent& transform);
};
