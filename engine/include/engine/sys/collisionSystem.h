#pragma once

#include <engine/sys/_system.h>
#include <engine/entity.h>
#include <engine/comp/collider.h>

class CollisionSystem : public System {
    static bool CheckTriangleCollision(Collider& collider1, Collider& collider2, int startX, int startY);
public:
    static bool CheckCollision(Entity& entity1, Entity& entity2);
};
