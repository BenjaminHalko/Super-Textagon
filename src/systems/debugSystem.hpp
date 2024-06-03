#pragma once

#include "_system.hpp"
#include "../debug.hpp"
#include "../input.hpp"

class DebugSystem : public System {
public:
    void UpdateEntity(Entity& entity) override {
        // No need to do anything here
    }

    void PreUpdate() override {
        if (Input::GetKeyPressed(Key::LEFT))
            Print("Left key pressed");

        if (Input::GetKeyPressed(Key::RIGHT))
            Print("Right key pressed");
    }
};
