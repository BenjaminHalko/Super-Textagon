#pragma once

#include <engine/comp/_uniqueComponent.h>

/**
 * @brief A component that represents the position, scale, and rotation of an entity.
 */
class TransformComponent : public UniqueComponent {
public:
    float x, y;
    float x_scale = 1, y_scale = 1;
    float rotation = 0;

    TransformComponent(float x, float y) : x(x), y(y) {}
    TransformComponent(float x, float y, float x_scale, float y_scale) : x(x), y(y), x_scale(x_scale), y_scale(y_scale) {}
    TransformComponent(float x, float y, float rotation) : x(x), y(y), rotation(rotation) {}
    TransformComponent(float x, float y, float x_scale, float y_scale, float rotation) : x(x), y(y), x_scale(x_scale), y_scale(y_scale), rotation(rotation) {}
};
