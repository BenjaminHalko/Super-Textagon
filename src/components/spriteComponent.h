#pragma once

#include "_component.h"
#include <vector>
#include <iterator>

/**
 * @brief A component that represents a sprite.
 * @details A sprite is a collection of points that are drawn on the screen.
 */
class SpriteComponent : public Component {
private:
    struct Point {
        float x, y;
        unsigned int color;
        float alpha;
    };
    std::vector<Point> _sprite;
public:
    SpriteComponent(std::initializer_list<Point> sprite) {
        std::copy(sprite.begin(), sprite.end(), std::back_inserter(_sprite));
    }
    std::vector<Point>& operator()() { return _sprite; }
};
