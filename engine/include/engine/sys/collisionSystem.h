#pragma once

#include <engine/sys/_system.h>
#include <engine/entity.h>
#include <engine/comp/colliderComponent.h>

class CollisionSystem : public System {
    static bool CheckTriangleCollision(ColliderComponent& collider1, ColliderComponent& collider2);
public:
    static bool CheckCollision(Entity& entity1, Entity& entity2);
};
