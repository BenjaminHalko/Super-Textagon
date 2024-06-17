#include "wall.h"
#include "../helper.h"
#include <engine/engine.h>
#include <engine/comp/depth.h>
#include <engine/comp/transform.h>
#include <engine/comp/sprite.h>
#include <engine/comp/script.h>
#include <engine/sys/timeSystem.h>

void CreateWall(int dir) {
    // Create wall script
    // This needs to be done so that the walls do not share static variables
    // There is probably a better way to do this, but this works for now
    auto script = [](Entity& self) {
        // Define static variables
        static float distance = 1.0f;
        static auto& sprite = self.GetComponent<Sprite>();
        static auto& transform = self.GetComponent<Transform>();

        // Update distance
        distance -= 0.1f * TimeSystem::DeltaTime();
    };

    float alpha = (dir % 2 == 0) ? 1 : 0.6f;
    dir *= 60;

    const float startDist = 0.15f;
    const float size = 0.04f;

    Sprite sprite = {
        {{startDist, 0}, 0, alpha},
        {{LengthDir_x(startDist, 60), LengthDir_y(startDist, 60)}, 0, alpha},
        {{startDist + size, 0}, 0, alpha},

        // Other half of trapezoid
        {{startDist + size, 0}, 0, alpha},
        {{LengthDir_x(startDist + size, 60), LengthDir_y(startDist + size, 60)}, 0, alpha},
        {{LengthDir_x(startDist, 60), LengthDir_y(startDist, 60)}, 0, alpha}
    };

    Engine::AddEntity(
        Depth(-50),
        Script(script),
        Transform(0, 0, 1, 1, (float)dir),
        Sprite(sprite)
    );
}

