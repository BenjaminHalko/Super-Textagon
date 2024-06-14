#include <engine/sys/_system.h>
#include <engine/common.h>
#include <engine/comp/transform.h>
#include <engine/comp/sprite.h>
#include <engine/comp/collider.h>

class TransformSystem : public System {
public:
    static void TranslatePoint(Point& point, float x, float y);
    static void ScalePoint(Point& point, float x_scale, float y_scale);
    static void RotatePoint(Point& point, float angle);
    static void ApplyTransformation(Point& point, Transform& transform);
    static SpriteComponent TransformSprite(SpriteComponent& sprite, Transform& transform);
    static Collider TransformCollider(Collider& collider, Transform& transform);
};
