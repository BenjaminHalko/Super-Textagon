#include <engine/comp/gravityComponent.h>

GravityComponent& GravityComponent::operator=(float gravity) {
    this->_gravity = gravity;
    return *this;
}

float GravityComponent::operator()() const {
    return this->_gravity;
}
