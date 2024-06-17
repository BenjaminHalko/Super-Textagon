#include "player.h"
#include "../helper.h"
#include <engine/engine.h>
#include <engine/comp/depth.h>
#include <engine/comp/transform.h>
#include <engine/comp/sprite.h>
#include <engine/comp/script.h>
#include <engine/sys/input.h>
#include <engine/sys/timeSystem.h>

void PlayerUpdate(Entity& self) {
    // Input
    bool left = Input::GetKeyDown(VK_LEFT) || Input::GetKeyDown('A');
    bool right = Input::GetKeyDown(VK_RIGHT) || Input::GetKeyDown('D');
    int dir = right - left;

    // Move Based on Input
    self.GetComponent<Transform>().rotation += (float)dir * 12 * TimeSystem::DeltaTime();
}

void CreatePlayer() {
    const float xOffset = 0.055f;
    const float size = 0.015f;
    Sprite sprite{
        {{xOffset + size, 0}, 0x00FFFF, 1},
        {{xOffset + LengthDir_x(size, 120), LengthDir_y(size, 120)}, 0x00AAFF, 0.9f},
        {{xOffset + LengthDir_x(size, 240), LengthDir_y(size, 240)}, 0x00AAFF, 0.9f}
    };

    Engine::AddEntity(
        Depth(0),
        Transform(0, 0),
        Sprite(sprite),
        Script(PlayerUpdate)
    );
}
