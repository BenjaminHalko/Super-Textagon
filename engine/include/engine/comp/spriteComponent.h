#pragma once

#include <engine/comp/_uniqueComponent.h>
#include <engine/common.h>
#include <vector>
#include <iterator>

#define Color unsigned int

struct ColoredPoint {
    Point point;
    Color color;
    float alpha;
};

/**
 * @brief A component that represents a sprite.
 * @details A sprite is a collection of points that are drawn on the screen.
 */
class SpriteComponent : public UniqueComponent {
private:
    std::vector<ColoredPoint> _sprite;
public:
    SpriteComponent() = default;

    SpriteComponent(std::initializer_list<ColoredPoint> sprite);

    explicit SpriteComponent(std::vector<ColoredPoint> sprite);

    explicit SpriteComponent(int size);

    SpriteComponent(
        float radius,
        int numSides,
        Color innerColor,
        float innerAlpha,
        Color outerColor,
        float outerAlpha
    );

    ColoredPoint& operator[](int index);

    void AddPoint(ColoredPoint point);

    size_t Size();

    std::vector<ColoredPoint>::iterator begin();

    std::vector<ColoredPoint>::iterator end();
};
