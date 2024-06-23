#include "core.h"
#include "../global.h"
#include "../helper.h"
#include <engine/engine.h>
#include <engine/comp/depth.h>
#include <engine/comp/sprite.h>
#include <engine/comp/transform.h>
#include <engine/comp/script.h>
#include <engine/sys/cameraSystem.h>

// Update the corse size/colors
void CoreUpdate(Entity& self) {
    static auto originalSprite = self.GetComponent<Sprite>();
    static auto &sprite = self.GetComponent<Sprite>();
    static auto &transform = self.GetComponent<Transform>();

    if (Global::beatPulse && !Global::gameOver && CameraSystem::zoom < 1.1f) {
        sprite.tintAlpha = 0.4f;
    }
    sprite.tintAlpha = Approach(sprite.tintAlpha, 0, 0.1f);

    ZoomSprite(sprite, originalSprite, Global::zoom);

    // Update sprite center zoom
    for(int i = 3 * 6; i < sprite.Size(); i++) {
        sprite[i].point.x *= fmax(0.01f, CameraSystem::zoom - 1.0f) * 0.2f;
        sprite[i].point.y *= fmax(0.01f, CameraSystem::zoom - 1.0f) * 0.2f;
    }

    // Update Sprite
    for(auto &point : sprite)
        point.color = MergeColors(
            MakeColor(Global::lastHue, 1.0, point.alpha),
            MakeColor(Global::hue, 1.0, point.alpha),
            Global::hueShift
        );
}

// Creates a core entity (middle you rotate around)
void CreateCore() {
    auto sprite = Sprite(0.04f, 6, 0, 0, MakeColor(Global::hue, 1.0f, 0.8f), 0.8f);
    for (auto& point : Sprite(0.038f, 6, 0, 0.2f, 0, 0.2f))
        sprite.AddPoint(point);

    auto& core = Engine::AddEntity(
        Depth(-100),
        Transform(0, 0),
        Sprite(sprite),
        Script(CoreUpdate)
    );
    CoreUpdate(core);
}
