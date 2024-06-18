#pragma once

#include <engine/comp/_component.h>

/**
 * @brief A component that represents the position, scale, and rotation of an entity.
 */
class Transform : public Component {
public:
    float x, y; 
    float x_scale = 1, y_scale = 1;
    float rotation = 0; 

    /**
     * @brief Constructs a Transform with the given position.
     *
     * @param x The x-coordinate of the position.
     * @param y The y-coordinate of the position.
     */
    Transform(float x, float y);

    /**
     * @brief Constructs a Transform with the given position and scale.
     *
     * @param x The x-coordinate of the position.
     * @param y The y-coordinate of the position.
     * @param x_scale The scale factor along the x-axis.
     * @param y_scale The scale factor along the y-axis.
     */
    Transform(float x, float y, float x_scale, float y_scale);

    /**
     * @brief Constructs a Transform with the given position and rotation.
     *
     * @param x The x-coordinate of the position.
     * @param y The y-coordinate of the position.
     * @param rotation The rotation angle in degrees.
     */
    Transform(float x, float y, float rotation);

    /**
     * @brief Constructs a Transform with the given position, scale, and rotation.
     *
     * @param x The x-coordinate of the position.
     * @param y The y-coordinate of the position.
     * @param x_scale The scale factor along the x-axis.
     * @param y_scale The scale factor along the y-axis.
     * @param rotation The rotation angle in degrees.
     */
    Transform(float x, float y, float x_scale, float y_scale, float rotation);
};