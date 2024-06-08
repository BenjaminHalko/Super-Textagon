#include "_system.h"
#include "../common.h"
#include "../components/transformComponent.h"
#include "../components/spriteComponent.h"

class TransformSystem : public System {
public:
    static void TranslatePoint(Point& point, float x, float y);
    static void ScalePoint(Point& point, float x_scale, float y_scale);
    static void RotatePoint(Point& point, float angle);
    static void ApplyTransformation(Point& point, TransformComponent& transform);
    static SpriteComponent TransformSprite(SpriteComponent& sprite, TransformComponent& transform);
};
