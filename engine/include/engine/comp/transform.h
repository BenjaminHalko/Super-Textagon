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

    Transform(float x, float y);
    Transform(float x, float y, float x_scale, float y_scale);
    Transform(float x, float y, float rotation);
    Transform(float x, float y, float x_scale, float y_scale, float rotation);
};
