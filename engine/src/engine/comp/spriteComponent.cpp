#include <engine/comp/spriteComponent.h>

SpriteComponent::SpriteComponent(std::initializer_list<ColoredPoint> sprite) {
    std::copy(sprite.begin(), sprite.end(), std::back_inserter(_sprite));
}

SpriteComponent::SpriteComponent(int size) {
    _sprite.reserve(size);
}

ColoredPoint& SpriteComponent::operator[](int index) {
    return _sprite[index];
}

void SpriteComponent::AddPoint(ColoredPoint point) {
    _sprite.push_back(point);
}

size_t SpriteComponent::Size() {
    return _sprite.size();
}

// Begin and end for range-based for loops
std::vector<ColoredPoint>::iterator SpriteComponent::begin() {
    return _sprite.begin();
}

std::vector<ColoredPoint>::iterator SpriteComponent::end() {
    return _sprite.end();
}
