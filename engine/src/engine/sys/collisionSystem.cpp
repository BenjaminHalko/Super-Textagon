#include <engine/sys/collisionSystem.h>
#include <engine/sys/transformSystem.h>
#include <engine/comp/collider.h>
#include <engine/comp/transform.h>
#include "engine/comp/tag.h"

float sign(Point p1, Point p2, Point p3) {
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle(Point pt, Point v1, Point v2, Point v3) {
    float d1, d2, d3;
    bool has_neg, has_pos;

    d1 = sign(pt, v1, v2);
    d2 = sign(pt, v2, v3);
    d3 = sign(pt, v3, v1);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}


int orientation(Point p, Point q, Point r) {
    float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0; // collinear
    return (val > 0) ? 1 : 2; // clock or counterclockwise
}

bool onSegment(Point p, Point q, Point r) {
    return q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y);
}
bool EdgeIntersection(Point p1, Point q1, Point p2, Point q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) return true;

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}


bool CollisionSystem::CheckTriangleCollision(Collider& collider1, Collider& collider2, int start1, int start2) {
    // Check if using any of the special colliders
    if (collider1.Size() == 1) {


        return PointInTriangle(collider1[0], collider2[start2], collider2[start2+1], collider2[start2+2]);
    } else if (collider2.Size() == 1) {
        return PointInTriangle(collider2[0], collider1[start1], collider1[start1+1], collider1[start1+2]);
    }

    // Get the triangles
    Point tri1[3] = {
        collider1[start1],
        collider1[start1+1],
        collider1[start1+2]
    };

    Point tri2[3] = {
        collider2[start2],
        collider2[start2+1],
        collider2[start2+2]
    };

    // Check if any vertex of one triangle is inside the other triangle
    for (auto pt : tri1) {
        if (PointInTriangle(pt, tri2[0], tri2[1], tri2[2])) {
            return true;
        }
    }
    for (auto pt : tri2) {
        if (PointInTriangle(pt, tri1[0], tri1[1], tri1[2])) {
            return true;
        }
    }


    // Check if any edges intersect
    std::vector<std::pair<Point, Point>> edges1 = { {tri1[0], tri1[1]}, {tri1[1], tri1[2]}, {tri1[2], tri1[0]} };
    std::vector<std::pair<Point, Point>> edges2 = { {tri2[0], tri2[1]}, {tri2[1], tri2[2]}, {tri2[2], tri2[0]} };

    for (const auto& edge1 : edges1) {
        for (const auto& edge2 : edges2) {
            if (EdgeIntersection(edge1.first, edge1.second, edge2.first, edge2.second)) {
                return true;
            }
        }
    }

    return false;
}

bool CollisionSystem::CheckCollision(Entity& entity1, Entity& entity2) {
    // Check if either entity is deleted
    if (entity1.IsDeleted() || entity2.IsDeleted())
        return false;

    // Get the original colliders and positions
    auto originalCollider1 = entity1.GetComponent<Collider>();
    auto originalCollider2 = entity2.GetComponent<Collider>();
    auto position1 = entity1.GetComponent<Transform>();
    auto position2 = entity2.GetComponent<Transform>();

    // Transform colliders to their current position
    auto transformedCollider1 = TransformSystem::TransformCollider(originalCollider1, position1);
    auto transformedCollider2 = TransformSystem::TransformCollider(originalCollider2, position2);

    // Loop through all triangles in collider1 and collider2
    for(int i = 0; i < transformedCollider1.Size(); i += 3) {
        for(int j = 0; j < transformedCollider2.Size(); j += 3) {
            if(CheckTriangleCollision(transformedCollider1, transformedCollider2, i, j)) {
                return true;
            }
        }
    }

    return false;
}
