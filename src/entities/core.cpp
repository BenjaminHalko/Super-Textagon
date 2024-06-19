#include "core.h"
#include "../global.h"
#include "../helper.h"
#include <engine/engine.h>
#include <engine/comp/depth.h>
#include <engine/comp/sprite.h>
#include <engine/comp/transform.h>
#include <engine/comp/script.h>
#include <engine/sys/cameraSystem.h>

void CoreUpdate(Entity& self) {
    static auto originalSprite = self.GetComponent<Sprite>();
    static auto &sprite = self.GetComponent<Sprite>();
    static auto &transform = self.GetComponent<Transform>();

    if (Global::beatPulse && !Global::gameOver && CameraSystem::zoom < 1.1f) {
        sprite.tintAlpha = 0.4f;
    }
    sprite.tintAlpha = Approach(sprite.tintAlpha, 0, 0.1f);

    ZoomSprite(sprite, originalSprite, Global::zoom);

    // Update Sprite
    for(auto &point : sprite)
        point.color = MakeColor(Global::hue, 1.0f, point.alpha);
}

void CreateCore() {
    auto& core = Engine::AddEntity(
        Depth(-100),
        Transform(0, 0),
        Sprite(0.04f, 6, 0x000000, 0, MakeColor(Global::hue, 1.0f, 0.8f), 0.8f),
        Script(CoreUpdate)
    );

    CoreUpdate(core);
}
