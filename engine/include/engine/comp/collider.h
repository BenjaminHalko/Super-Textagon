#pragma once

#include <engine/comp/_propertyComponent.h>
#include <engine/comp/sprite.h>
#include <vector>
#include <engine/common.h>
#include <iterator>

class Collider : public PropertyComponent {
    std::vector<Point> _points;
public:
    Collider() = default;

    Collider(std::initializer_list<Point> points);

    explicit Collider(Sprite& sprite);

    explicit Collider(int size);

    Point& operator[](int index);

    void AddPoint(Point point);

    size_t Size();

    std::vector<Point>::iterator begin();

    std::vector<Point>::iterator end();
};
