#pragma once

#include <engine/comp/_component.h>
#include <engine/comp/sprite.h>
#include <vector>
#include <engine/common.h>
#include <iterator>

/**
 * @brief A component for handling colliders in the engine.
 *
 * @details Handles colliders within the game engine.
 * Uses given points, either using a sprite or size as a reference.
 */
class Collider : public Component {
    std::vector<Point> _points;
public:
    /**
     * @brief Default constructor for Collider.
     */
    Collider() = default;

    /**
     * @brief Constructs a Collider from an initializer list of points.
     *
     * @param points Initializer list of points to initialize the collider.
     */
    Collider(std::initializer_list<Point> points);

    /**
     * @brief Constructs a Collider from a sprite.
     *
     * @param sprite Reference to the sprite used to initialize the collider.
     */
    explicit Collider(Sprite& sprite);

    /**
     * @brief Constructs a Collider with a specified size.
     *
     * @param size The size used to initialize the collider.
     */
    explicit Collider(int size);

    /**
     * @brief Accesses the point at the given index.
     *
     * @param index The index of the point to access.
     * @return Reference to the point at the specified index.
     */
    Point& operator[](int index);

    /**
     * @brief Adds a point to the collider.
     *
     * @param point The point to add to the collider.
     */
    void AddPoint(Point point);

    /**
     * @brief Returns the number of points in the collider.
     *
     * @return The number of points in the collider.
     */
    size_t Size();

    /**
     * @brief Updates the collider based on the given sprite.
     *
     * @param sprite Reference to the sprite used to update the collider.
     */
    void Update(Sprite& sprite);

    /**
     * @brief Returns an iterator to the beginning of the points.
     *
     * @return Iterator to the beginning of the points.
     */
    std::vector<Point>::iterator begin();

    /**
     * @brief Returns an iterator to the end of the points.
     *
     * @return Iterator to the end of the points.
     */
    std::vector<Point>::iterator end();
};