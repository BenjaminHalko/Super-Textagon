#pragma once

#include "_component.h"

class GravityComponent : Component {
private:
    float _gravity;
public:
    GravityComponent(float gravity) : _gravity(gravity) {}
    void operator=(float gravity) { this->_gravity = gravity; }
    float operator()() { return _gravity; }
};
