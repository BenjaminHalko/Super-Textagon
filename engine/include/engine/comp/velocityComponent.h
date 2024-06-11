#pragma once

#include <engine/comp/_basicComponent.h>

class VelocityComponent : public BasicComponent {
public:
    float gravity = 0;
    float xSpeed = 0;
    float ySpeed = 0;
    float speed = 0;
    float direction = 0;
    float angularVelocity = 0;

    VelocityComponent() = default;
};
