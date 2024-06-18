#pragma once

#include <engine/comp/_component.h>
#include <engine/comp/sprite.h>
#include <vector>
#include <engine/common.h>
#include <iterator>

class Collider : public Component {
    std::vector<Point> _points;
public:
    Collider() = default;

    Collider(std::initializer_list<Point> points);

    explicit Collider(Sprite& sprite);

    explicit Collider(int size);

    Point& operator[](int index);

    void AddPoint(Point point);

    size_t Size();

    void Update(Sprite& sprite);

    std::vector<Point>::iterator begin();

    std::vector<Point>::iterator end();
};
