#pragma once

#include "_component.h"
#include "../common.h"
#include <vector>
#include <iterator>

/**
 * @brief A component that represents a sprite.
 * @details A sprite is a collection of points that are drawn on the screen.
 */
class SpriteComponent : public Component {
private:
    std::vector<ColoredPoint> _sprite;
public:
    SpriteComponent() = default;

    SpriteComponent(std::initializer_list<ColoredPoint> sprite) {
        std::copy(sprite.begin(), sprite.end(), std::back_inserter(_sprite));
    }

    ColoredPoint& operator[](int index) {
        return _sprite[index];
    }

    void AddPoint(ColoredPoint point) {
        _sprite.push_back(point);
    }

    // Begin and end for range-based for loops
    std::vector<ColoredPoint>::iterator begin() {
        return _sprite.begin();
    }

    std::vector<ColoredPoint>::iterator end() {
        return _sprite.end();
    }
};
