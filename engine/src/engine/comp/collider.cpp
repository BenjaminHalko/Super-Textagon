#include <engine/comp/collider.h>
#include <iterator>

Collider::Collider(std::initializer_list<Point> points) {
    _points.resize(points.size());
    std::copy(points.begin(), points.end(), _points.begin());
}

Collider::Collider(Sprite& sprite) {
    Update(sprite);
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

void Collider::Update(Sprite &sprite) {
    for (auto& point : sprite) {
        _points.push_back(point.point);
    }
}

std::vector<Point>::iterator Collider::begin() {
    return _points.begin();
}

std::vector<Point>::iterator Collider::end() {
    return _points.end();
}
