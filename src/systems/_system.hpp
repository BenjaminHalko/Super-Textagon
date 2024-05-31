#pragma once

#include "../entities/_entity.hpp"

class System {
public:
    virtual ~System() = default;

    virtual void StepBegin() = 0;
    virtual void Step(Entity &entity) = 0;
    virtual void StepEnd() = 0;
};
