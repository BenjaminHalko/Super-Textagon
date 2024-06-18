#pragma once

#include <engine/sys/_system.h>
#include <engine/comp/transform.h>

class CameraSystem : public System {
public:
    static float x, y, zoom, rotation;
    static Transform GetTransform();
};
