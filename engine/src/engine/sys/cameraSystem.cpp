#include <engine/sys/cameraSystem.h>

// Define the static variables
float CameraSystem::x = 0.5f;
float CameraSystem::y = 0.5f;
float CameraSystem::zoom = 1;
float CameraSystem::rotation = 0;

Transform CameraSystem::GetTransform() {
    return {x, y, zoom, zoom, rotation};
}
