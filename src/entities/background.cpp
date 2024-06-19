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
    static float zoom = 0.0;
    static float rotationSpeed = 0;
    static float phaseShift = 0;
    static auto& sprite = self.GetComponent<Sprite>();
    static bool phase2Dir = true;
    static float phase2Amount = 0;
    static int phase = 0;
    static float runtime = 0;

    // Decide Phase
    if (!Global::gameOver) {
        runtime = RoundRunning();
        if (runtime < 10.0f)
            phase = 0;
        else if (runtime < 20.0f)
            phase = 1;
        //else
            //phase = 2;
    }

    // Decide Speed
    if (Global::showGameOverUI)
        rotationSpeed = -1.0f;
    else if (phase == 0)
        rotationSpeed = 1.0f;
    else if (phase == 1)
        rotationSpeed = -1.0f;
    else
        rotationSpeed = 1.9f;

    // Rotate Background
    CameraSystem::rotation += rotationSpeed * TimeSystem::DeltaTime();

    // Pulse
    if (!Global::gameOver && Global::beatPulse)
        zoom = 1.0f;
    zoom = ApproachEase(zoom, 0.0f, 0.2f, 0.8f);
    Global::zoom = sinf(zoom * PI);

    // Phase 2 Hue Shift
    if (phase == 1) {
        phase2Amount = Approach(phase2Amount, phase2Dir, 0.02f);
        if (phase2Amount == (float)phase2Dir)
            phase2Dir = !phase2Dir;
    }

    // Update Hue
    float phase1Hue = Wave(0, 54, 5, 0);
    auto phase2Hue = (float)std::lerp(30, 140, std::abs(fmod(runtime, 4) - 2) / 2.0f);
    phaseShift = Approach(phaseShift, (float)phase, 0.1f);
    Global::hue = (float)std::lerp(phase1Hue, phase2Hue, fmin(1, phaseShift));

    // Update Color
    if (phase == 1) {
        for(int i = 0; i < sprite.Size(); i++) {
            auto &point = sprite[i];
            point.alpha = 0.3f;
            if ((i % 6 >= 3) == (fmod(Global::musicTime, 4) >= 2))
                point.color = MakeColor(Global::hue, 1.0f, point.alpha);
            else
                point.color = 0;
        }
    } else {
        for(int i = 0; i < sprite.Size(); i++) {
            auto &point = sprite[i];
            point.alpha = (i % 6 >= 3) ? 0.4f : 0.2f;
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
