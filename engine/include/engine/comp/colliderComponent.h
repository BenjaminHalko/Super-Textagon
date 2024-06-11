#pragma once

#include <engine/comp/_basicComponent.h>
#include <engine/comp/spriteComponent.h>
#include <vector>
#include <engine/common.h>
#include <iterator>

class ColliderComponent : public BasicComponent {
    std::vector<Point> _points;
public:
    ColliderComponent() = default;

    ColliderComponent(std::initializer_list<Point> points);

    explicit ColliderComponent(SpriteComponent& sprite);

    explicit ColliderComponent(int size);

    Point& operator[](int index);

    void AddPoint(Point point);

    size_t Size();

    std::vector<Point>::iterator begin();

    std::vector<Point>::iterator end();
};
