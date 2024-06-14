#include <engine/comp/collider.h>
#include <iterator>

Collider::Collider(std::initializer_list<Point> points) {
    std::copy(_points.begin(), _points.end(), std::back_inserter(_points));
}

Collider::Collider(Sprite& sprite) {
    for (auto& point : sprite) {
        _points.push_back(point.point);
    }
}

Collider::Collider(int size) {
    _points.resize(size);
}

Point& Collider::operator[](int index) {
    return _points[index];
}

void Collider::AddPoint(Point point) {
    _points.push_back(point);
}

size_t Collider::Size() {
    return _points.size();
}

std::vector<Point>::iterator Collider::begin() {
    return _points.begin();
}

std::vector<Point>::iterator Collider::end() {
    return _points.end();
}
