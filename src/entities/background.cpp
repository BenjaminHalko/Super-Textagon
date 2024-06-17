#include "background.h"
#include "../helper.h"
#include "../global.h"
#include <engine/engine.h>
#include <engine/comp/depth.h>
#include <engine/comp/sprite.h>
#include <engine/comp/transform.h>
#include <engine/comp/script.h>
#include <engine/sys/cameraSystem.h>
#include <engine/sys/timeSystem.h>

void BackgroundUpdate(Entity& self) {
    // Rotate Background
    CameraSystem::rotation -= 1.9f * TimeSystem::DeltaTime();

    // Pulse Background
    if (Global::beatPulse) {
        //CameraSystem::zoom = 1.4f;
    }
    //CameraSystem::zoom = Approach(CameraSystem::zoom, 1.0f, 0.03f);

    // Update Hue Based on Time
    Global::hue = Wave(0, 54, 5, 0);

    // Update Colors of All Entities
    for (auto entity : Engine::GetEntities<Sprite>()) {
        auto &sprite = entity->GetComponent<Sprite>();
        for(auto &point : sprite) {
            point.color = MakeColor(Global::hue, 1.0f, point.alpha);
        }
    }
}

void CreateBackground() {
    // Generate Sprite
    const float size = 1.2f;
    const int angle = 60;

    auto sprite = Sprite(3 * 6);
    for(int i = 0; i < 6; i++) {
        Color col = (i % 2 == 0) ? 0x00505f : 0x003741;
        float alpha = (i % 2 == 0) ? 0.4f : 0.2f;
        float dir = (float)i * angle;

        sprite[i * 3] = {0, 0, col, alpha};
        sprite[i * 3 + 1] = {
            LengthDir_x(size, dir), LengthDir_y(size, dir), col, alpha
        };
        sprite[i * 3 + 2] = {
            LengthDir_x(size, dir + angle), LengthDir_y(size, dir + angle), col, alpha
        };
    }

    // Add Entity
    Engine::AddEntity(
        Depth(100),
        Sprite(sprite),
        Transform(0, 0),
        Script(BackgroundUpdate)
    );
}
