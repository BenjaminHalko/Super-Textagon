#include <engine/comp/collider.h>
#include <iterator>

Collider::Collider(std::initializer_list<Vector2> points) {
    _points.resize(points.size());
    std::copy(points.begin(), points.end(), _points.begin());
}

Collider::Collider(Sprite& sprite) {
    Update(sprite);
}

Collider::Collider(int size) {
    _points.resize(size);
}

Vector2& Collider::operator[](int index) {
    return _points[index];
}

void Collider::AddPoint(Vector2 point) {
    _points.push_back(point);
}

size_t Collider::Size() {
    return _points.size();
}

void Collider::Update(Sprite &sprite) {
    _points.clear();
    for (auto& point : sprite) {
        _points.push_back(point.point);
    }
}

std::vector<Vector2>::iterator Collider::begin() {
    return _points.begin();
}

std::vector<Vector2>::iterator Collider::end() {
    return _points.end();
}
