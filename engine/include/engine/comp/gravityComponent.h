#pragma once

#include <engine/comp/_component.h>

class GravityComponent : public Component {
private:
    float _gravity;
public:
    explicit GravityComponent(float gravity) : _gravity(gravity) {}
    GravityComponent& operator=(float gravity);
    float operator()() const;
};
