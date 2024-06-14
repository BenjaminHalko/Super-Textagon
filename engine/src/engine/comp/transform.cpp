#include <engine/comp/transform.h>

Transform::Transform(float x, float y)
    : x(x), y(y) {}
Transform::Transform(float x, float y, float x_scale, float y_scale)
    : x(x), y(y), x_scale(x_scale), y_scale(y_scale) {}
Transform::Transform(float x, float y, float rotation)
    : x(x), y(y), rotation(rotation) {}
Transform::Transform(float x, float y, float x_scale, float y_scale, float rotation)
    : x(x), y(y), x_scale(x_scale), y_scale(y_scale), rotation(rotation) {}
