#include <engine/sys/collisionSystem.h>
#include <engine/sys/transformSystem.h>
#include <engine/comp/colliderComponent.h>
#include <engine/comp/transformComponent.h>

bool CollisionSystem::CheckTriangleCollision(ColliderComponent& collider1, ColliderComponent& collider2) {
    // Check if any triangle from collider1 intersects with any triangle from collider2
    return true;
}

bool CollisionSystem::CheckCollision(Entity& entity1, Entity& entity2) {
    // Get the original colliders and positions
    auto originalCollider1 = entity1.GetComponent<ColliderComponent>();
    auto originalCollider2 = entity1.GetComponent<ColliderComponent>();
    auto position1 = entity1.GetComponent<TransformComponent>();
    auto position2 = entity2.GetComponent<TransformComponent>();

    // Transform colliders to their current position
    auto collider1 = TransformSystem::TransformCollider(originalCollider1, position1);
    auto collider2 = TransformSystem::TransformCollider(originalCollider2, position2);

    // These represent triangles
    ColliderComponent colliderToCheck1(3);
    ColliderComponent colliderToCheck2(3);

    // Loop through all triangles in collider1 and collider2
    for(int i = 0; i < collider1.Size(); i += 3) {
        std::copy(colliderToCheck1.begin(), colliderToCheck1.end(), collider1.begin() + i);

        for(int j = 0; j < collider2.Size(); j += 3) {
            std::copy(colliderToCheck2.begin(), colliderToCheck2.end(), collider2.begin() + j);

            if(CheckTriangleCollision(colliderToCheck1, colliderToCheck2)) {
                return true;
            }
        }
    }

    return false;
}
