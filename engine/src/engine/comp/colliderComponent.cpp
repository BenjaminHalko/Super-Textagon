#include <engine/comp/colliderComponent.h>
#include <iterator>

ColliderComponent::ColliderComponent(std::initializer_list<Point> points) {
    std::copy(_points.begin(), _points.end(), std::back_inserter(_points));
}

ColliderComponent::ColliderComponent(SpriteComponent& sprite) {
    for (auto& point : sprite) {
        _points.push_back(point.point);
    }
}

ColliderComponent::ColliderComponent(int size) {
    _points.resize(size);
}

Point& ColliderComponent::operator[](int index) {
    return _points[index];
}

void ColliderComponent::AddPoint(Point point) {
    _points.push_back(point);
}

size_t ColliderComponent::Size() {
    return _points.size();
}

std::vector<Point>::iterator ColliderComponent::begin() {
    return _points.begin();
}

std::vector<Point>::iterator ColliderComponent::end() {
    return _points.end();
}
