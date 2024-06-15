#include "_testEntity.h"
#include "engine/engine.h"
#include "engine/comp/script.h"
#include "../global.h"
#include "engine/sys/timeSystem.h"
#include "engine/comp/transform.h"
#include "../helper.h"

void UpdateTestEntity(Entity& self) {
    // Define Variables
    static auto &transform = self.GetComponent<Transform>();
    static auto &sprite = self.GetComponent<Sprite>();
    sprite.tint = 0x00AAFF;

    // Pulse on Beat
    if (Global::beatPulse)
        sprite.tintAlpha = 1;

    // Ease back to normal
    sprite.tintAlpha = ApproachEase(sprite.tintAlpha, 0.0f, 0.05f, 0.8f);

    // Also affect scale and rotation
    sprite.alpha = 1 - sprite.tintAlpha * 0.5f;
    transform.x_scale = 1 + sprite.tintAlpha * 0.5f;
    transform.y_scale = transform.x_scale;
    transform.rotation += TimeSystem::DeltaTime() * (1 + sprite.tintAlpha * 5);
}

void CreateTestEntity() {
    Engine::AddEntity(
        "test", 0,
        Transform(0.5f, 0.5f),
        Sprite(0.2f, 3, 0xFFFFFF, 1, 0xFF0000, 0.5f),
        Script(UpdateTestEntity)
    );
}
