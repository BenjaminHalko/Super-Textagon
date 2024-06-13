#pragma once

#include <engine/sys/_system.h>

class EntityUpdateSystem : public System {
    friend class Engine;
    static void Update();
};
