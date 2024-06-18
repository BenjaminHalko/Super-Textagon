#include <engine/comp/sprite.h>
#include <cmath>

Sprite::Sprite(std::initializer_list<ColoredPoint> sprite) {
    std::copy(sprite.begin(), sprite.end(), std::back_inserter(_sprite));
}

Sprite::Sprite(std::vector<ColoredPoint> sprite) {
    std::copy(sprite.begin(), sprite.end(), std::back_inserter(_sprite));
}

Sprite::Sprite(int size) {
    _sprite.resize(size);
}

Sprite::Sprite(
    float radius,
    int numSides,
    Color innerColor,
    float innerAlpha,
    Color outerColor,
    float outerAlpha,
    float originX,
    float originY,
    float rotation
) {
    for (int i = 0; i < numSides; i++) {
        float angle = 2 * PI * (float) i / (float) numSides + rotation;
        _sprite.push_back({{originX + radius * cosf(angle), originY + radius * sinf(angle)}, outerColor, outerAlpha});
        angle = 2 * PI * (float) (i + 1) / (float) numSides + rotation;
        _sprite.push_back({{originX + radius * cosf(angle), originY + radius * sinf(angle)}, outerColor, outerAlpha});
        _sprite.push_back({{originX, originY}, innerColor, innerAlpha});
    }
}

ColoredPoint& Sprite::operator[](int index) {
    return _sprite[index];
}

void Sprite::AddPoint(ColoredPoint point) {
    _sprite.push_back(point);
}

size_t Sprite::Size() {
    return _sprite.size();
}

// Begin and end for range-based for loops
std::vector<ColoredPoint>::iterator Sprite::begin() {
    return _sprite.begin();
}

std::vector<ColoredPoint>::iterator Sprite::end() {
    return _sprite.end();
}
