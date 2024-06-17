#include "core.h"
#include "../global.h"
#include "../helper.h"
#include <engine/engine.h>
#include <engine/comp/depth.h>
#include <engine/comp/sprite.h>
#include <engine/comp/transform.h>
#include <engine/comp/script.h>

void CoreUpdate(Entity& self) {
    static auto &sprite = self.GetComponent<Sprite>();

    if (Global::beatPulse) {
        sprite.tintAlpha = 0.4f;
    }
    sprite.tintAlpha = Approach(sprite.tintAlpha, 0, 0.1f);
}

void CreateCore() {
    Engine::AddEntity(
        Depth(-100),
        Transform(0, 0),
        Sprite(0.04f, 6, 0xFF0000, 0, 0xFFFFFF, 0.8f),
        Script(CoreUpdate)
    );
}
