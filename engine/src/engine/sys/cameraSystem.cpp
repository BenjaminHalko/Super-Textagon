#include <engine/sys/cameraSystem.h>

// Define the static variables
TransformComponent CameraSystem::_cameraTransform(0.0f, 0.0f);

TransformComponent& CameraSystem::GetCameraTransform() {
    return _cameraTransform;
}
