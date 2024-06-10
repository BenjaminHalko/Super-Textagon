#pragma once

/**
 * @brief Base class for all systems
 */
class System {
public:
    // It is important to have a virtual destructor
    virtual ~System() = default;
    virtual void Update() = 0;
};
