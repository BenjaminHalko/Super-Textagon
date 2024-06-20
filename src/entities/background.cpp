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
    static auto& sprite = self.GetComponent<Sprite>();
    static auto& transform = self.GetComponent<Transform>();
    static int phase = 0;
    static float runtime = 0;

    // Rotate Background
    if (!Global::intro) {
        if (phase == 0)
            transform.rotation = 0;
        CameraSystem::rotation += rotationSpeed * TimeSystem::DeltaTime();
    } else {
        transform.rotation += rotationSpeed * TimeSystem::DeltaTime();
    }

    // Decide Phase
    if (!Global::gameOver) {
        runtime = RoundRunning();
        if (runtime < 20.0f) {
            if (phase != 1) {
                Global::hueShift = 0;
                Global::lastHue = Global::hue;
            }
            phase = 1;
        } else if (runtime < 40.0f) {
            if (phase != 2) {
                Global::hueShift = 0;
                Global::lastHue = Global::hue;
            }
            phase = 2;
        } else {
            if (phase != 3) {
                Global::hueShift = 0;
                Global::lastHue = Global::hue;
            }
            phase = 3;
        }
    }

    // Decide Speed
    if (Global::intro) {
        rotationSpeed = -0.5f;
    } else if (Global::showGameOverUI)
        rotationSpeed = -1.0f;
    else if (runtime < 9.0f)
        rotationSpeed = 1.0f;
    else if (runtime < 12.0f)
        rotationSpeed = -1.0f;
    else
        rotationSpeed = (1.4f + 0.4f * (float)GetShapePhase()) * float(fmod(runtime, 16) < 8 ? -1 : 1);

    // Pulse
    if (!Global::intro) {
        if (!Global::gameOver && Global::beatPulse)
            zoom = 1.0f;
        zoom = ApproachEase(zoom, 0.0f, 0.2f, 0.8f);
        Global::zoom = sinf(zoom * PI);
    }

    // Update Hue
    if (phase == 1)
        Global::hue = Wave(0, 54, 5, 0);
    else if (phase == 2)
        Global::hue = (float)std::lerp(30, 140, std::abs(fmod(runtime, 4) - 2) / 2.0f);
    else {
        const float hues[6] = {106, 264, 14, 189, 309, 62};
        float hue = hues[int(runtime / 2) % 6];
        if (Global::hue != hue) {
            Global::hueShift = 0;
            Global::lastHue = Global::hue;
            Global::hue = hue;
        }
    }
    Global::hueShift = Approach(Global::hueShift, 1, 0.02f);
    float brightness = 1;
    if (Global::intro)
        brightness = Clamp(floor((TimeSystem::TimeRunning() / 2.0f) * 5.0f) / 5.0f, 0, 1);

    // Update Color
    if (phase == 3) {
        for(int i = 0; i < sprite.Size(); i++) {
            auto &point = sprite[i];
            point.alpha = ((i % 6 >= 3) == (fmod(Global::musicTime, 4) >= 2)) ? 0.4f : 0.2f;
            point.color = MergeColors(
                MakeColor(Global::lastHue, 1.0, point.alpha),
                MakeColor(Global::hue, 1.0, point.alpha),
                Global::hueShift
            );
        }
    } else if (phase == 2) {
        for(int i = 0; i < sprite.Size(); i++) {
            auto &point = sprite[i];
            point.alpha = 0.3f;
            if ((i % 6 >= 3) == (fmod(Global::musicTime, 4) >= 2))
                point.color = MergeColors(
                    MakeColor(Global::lastHue, 1.0, point.alpha),
                    MakeColor(Global::hue, 1.0, point.alpha),
                    Global::hueShift
                );
            else
                point.color = 0;
        }
    } else {
        for(int i = 0; i < sprite.Size(); i++) {
            auto &point = sprite[i];
            point.alpha = (i % 6 >= 3) ? 0.4f : 0.2f;
            point.color = MergeColors(
                MakeColor(Global::lastHue, float(phase != 0), point.alpha * brightness),
                MakeColor(Global::hue, float(phase != 0), point.alpha * brightness),
                Global::hueShift
            );
        }
    }

    // Update Position
   if (Global::intro)
       transform.y = 0.1f;
   else
       transform.y = 0;
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
