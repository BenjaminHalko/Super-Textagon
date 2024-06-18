#pragma once

#include <engine/sys/_system.h>
#include <engine/entity.h>
#include <engine/comp/collider.h>

/**
 * @brief A system that handles collision detection between entities.
 */
class CollisionSystem : public System {
    /**
     * @brief Checks for a triangle-based collision between two colliders.
     *
     * @param collider1 The first collider.
     * @param collider2 The second collider.
     * @param startX The starting x-coordinate for the collision check.
     * @param startY The starting y-coordinate for the collision check.
     * @return True if a collision is detected, false otherwise.
     */
    static bool CheckTriangleCollision(Collider& collider1, Collider& collider2, int startX, int startY);
public:
    /**
     * @brief Checks for a collision between two entities.
     *
     * @param entity1 The first entity.
     * @param entity2 The second entity.
     * @return True if a collision is detected, false otherwise.
     */
    static bool CheckCollision(Entity& entity1, Entity& entity2);
};