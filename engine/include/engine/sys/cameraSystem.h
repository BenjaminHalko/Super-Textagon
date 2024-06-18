#pragma once

#include <engine/sys/_system.h>
#include <engine/comp/transform.h>

/**
 * @brief A system that manages the camera's position, zoom, and rotation.
 */
class CameraSystem : public System {
public:
    static float x, y;
    static float zoom;
    static float rotation;

    /**
     * @brief Retrieves the current transform of the camera.
     *
     * @return The transform representing the camera's current position, scale, and rotation.
     */
    static Transform GetTransform();
};