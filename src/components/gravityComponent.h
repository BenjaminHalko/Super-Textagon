#pragma once

#include "_component.h"

class GravityComponent : public Component {
private:
    float _gravity;
public:
    explicit GravityComponent(float gravity) : _gravity(gravity) {}
    GravityComponent& operator=(float gravity) {
        this->_gravity = gravity;
        return *this;
    }
    float operator()() const {
        return _gravity;
    }
};
