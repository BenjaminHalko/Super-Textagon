#pragma once

#include <engine/comp/_component.h>
#include <engine/common.h>
#include <vector>
#include <iterator>

#define Color unsigned int

/**
 * @brief Structure representing a point with color and alpha value.
 */
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

    /**
     * @brief Default constructor for Sprite.
     */
    Sprite() = default;

    /**
     * @brief Constructs a Sprite from an initializer list of colored points.
     *
     * @param sprite Initializer list of colored points to initialize the sprite.
     */
    Sprite(std::initializer_list<ColoredPoint> sprite);

    /**
     * @brief Constructs a Sprite from a vector of colored points.
     *
     * @param sprite Vector of colored points to initialize the sprite.
     */
    explicit Sprite(std::vector<ColoredPoint> sprite);

    /**
     * @brief Constructs a Sprite with a specified size.
     *
     * @param size The number of points to reserve for the sprite.
     */
    explicit Sprite(int size);

    /**
     * @brief Constructs a Sprite with specified parameters.
     *
     * @param radius The radius of the sprite.
     * @param numSides The number of sides for the sprite.
     * @param innerColor The inner color of the sprite.
     * @param innerAlpha The inner alpha transparency of the sprite.
     * @param outerColor The outer color of the sprite.
     * @param outerAlpha The outer alpha transparency of the sprite.
     * @param originX The x-coordinate of the origin of the sprite.
     * @param originY The y-coordinate of the origin of the sprite.
     * @param rotation The rotation of the sprite in degrees.
     */
    Sprite(
        float radius,
        int numSides,
        Color innerColor,
        float innerAlpha,
        Color outerColor,
        float outerAlpha,
        float originX = 0.0f,
        float originY = 0.0f,
        float rotation = 0.0f
    );

    /**
     * @brief Accesses the colored point at the given index.
     *
     * @param index The index of the colored point to access.
     * @return Reference to the colored point at the specified index.
     */
    ColoredPoint& operator[](int index);

    /**
     * @brief Adds a colored point to the sprite.
     *
     * @param point The colored point to add to the sprite.
     */
    void AddPoint(ColoredPoint point);

    /**
     * @brief Returns the number of points in the sprite.
     *
     * @return The number of points in the sprite.
     */
    size_t Size();

    /**
     * @brief Returns an iterator to the beginning of the colored points.
     *
     * @return Iterator to the beginning of the colored points.
     */
    std::vector<ColoredPoint>::iterator begin();

    /**
     * @brief Returns an iterator to the end of the colored points.
     *
     * @return Iterator to the end of the colored points.
     */
    std::vector<ColoredPoint>::iterator end();
};