#include "wallGenerator.h"
#include "wall.h"
#include "../global.h"
#include "../helper.h"
#include <engine/engine.h>
#include <engine/comp/script.h>
#include <engine/comp/depth.h>
#include <engine/sys/timeSystem.h>

#define StandardDistanceBetweenSets 0.3f

// The return value allows you to define extra spacing between the next set of walls
// Helper Patterns
float WallRing(int rotation, float dist) {
    CreateWall(rotation + 1, dist);
    CreateWall(rotation + 2, dist);
    CreateWall(rotation + 3, dist);
    CreateWall(rotation + 4, dist);
    CreateWall(rotation + 5, dist);
    return StandardDistanceBetweenSets;
}

// Wall patterns
float MultiWallRing(int rotation, float dist) {
    dist += WallRing(rotation, dist);
    dist += WallRing(rotation + 3, dist);
    dist += WallRing(rotation + 1, dist);
    return dist;
}

// Wall Generator
typedef float (*WallPatternFunc)(int, float);
void UpdateWallGenerator(Entity& self) {
    // Create array of functions
    static const std::vector<WallPatternFunc> wallSets = {
        MultiWallRing
    };

    // Config
    static const float startDistance = 1.0f;
    static float delayTillNextSet = 0.0f;

    // Create new set
    delayTillNextSet -= TimeSystem::DeltaTime() * Global::gameSpeed * BaseWallSpd;

    if (delayTillNextSet <= 0) {
        int pattern = (int)RandomRange(0, (float)wallSets.size());
        int rotation = (int)RandomRange(0, 6);
        delayTillNextSet = wallSets[pattern](rotation, startDistance + delayTillNextSet);
    }
}

void CreateWallGenerator() {
    Engine::AddEntity(
        Depth(90),
        Script(UpdateWallGenerator)
    );
}
