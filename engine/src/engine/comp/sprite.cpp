#include <engine/comp/sprite.h>

SpriteComponent::SpriteComponent(std::initializer_list<ColoredPoint> sprite) {
    std::copy(sprite.begin(), sprite.end(), std::back_inserter(_sprite));
}

SpriteComponent::SpriteComponent(std::vector<ColoredPoint> sprite) {
    std::copy(sprite.begin(), sprite.end(), std::back_inserter(_sprite));
}

SpriteComponent::SpriteComponent(int size) {
    _sprite.resize(size);
}

SpriteComponent::SpriteComponent(
    float radius,
    int numSides,
    Color innerColor,
    float innerAlpha,
    Color outerColor,
    float outerAlpha
) {
    for (int i = 0; i < numSides; i++) {
        float angle = 2 * PI * (float) i / (float) numSides;
        _sprite.push_back({{radius * cosf(angle), radius * sinf(angle)}, outerColor, outerAlpha});
        angle = 2 * PI * (float) (i + 1) / (float) numSides;
        _sprite.push_back({{radius * cosf(angle), radius * sinf(angle)}, outerColor, outerAlpha});
        _sprite.push_back({{0, 0}, innerColor, innerAlpha});
    }
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
