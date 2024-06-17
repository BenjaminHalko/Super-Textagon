#pragma once

#include <engine/comp/_component.h>
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
class Sprite : public Component {
private:
    std::vector<ColoredPoint> _sprite;
public:
    Color tint = 0xFFFFFF;
    float tintAlpha = 0;
    float alpha = 1;

    Sprite() = default;

    Sprite(std::initializer_list<ColoredPoint> sprite);

    explicit Sprite(std::vector<ColoredPoint> sprite);

    explicit Sprite(int size);

    Sprite(
        float radius,
        int numSides,
        Color innerColor,
        float innerAlpha,
        Color outerColor,
        float outerAlpha,
        float originX=0.0f,
        float originY=0.0f,
        float rotation=0.0f
    );

    ColoredPoint& operator[](int index);

    void AddPoint(ColoredPoint point);

    size_t Size();

    std::vector<ColoredPoint>::iterator begin();

    std::vector<ColoredPoint>::iterator end();
};
