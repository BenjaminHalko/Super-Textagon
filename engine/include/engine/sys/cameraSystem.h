#pragma once

#include <engine/sys/_system.h>
#include <engine/comp/transformComponent.h>

class CameraSystem : public System {
    static TransformComponent _cameraTransform;
public:
    static TransformComponent& GetCameraTransform();
};
