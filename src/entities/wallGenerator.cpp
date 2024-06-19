#include "wallGenerator.h"
#include "wall.h"
#include "../global.h"
#include "../helper.h"
#include <engine/engine.h>
#include <engine/comp/script.h>
#include <engine/comp/depth.h>
#include <engine/sys/timeSystem.h>

#define StandardDistanceBetweenSets 0.35f

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

float WallGaps(int rotation, float dist) {
    CreateWall(rotation, dist);
    CreateWall(rotation + 2, dist);
    CreateWall(rotation + 4, dist);
    return StandardDistanceBetweenSets;
}

// Wall patterns
float MultiWallRing(int rotation, float dist) {
    dist += WallRing(rotation, dist);
    dist += WallRing(rotation + 3, dist);
    WallRing(rotation + 1, dist);
    return StandardDistanceBetweenSets * 3;
}

float MultiWallGaps(int rotation, float dist) {
    dist += WallGaps(rotation, dist);
    dist += WallGaps(rotation + 1, dist);
    WallGaps(rotation, dist);
    return StandardDistanceBetweenSets * 3;
}

float SpinAround(int rotation, float dist) {
    const float distBetween = WallStandardSize * 0.5f;
    const int dir = 1;
    const float hallwaySize = WallStandardSize * 6.0f;

    CreateWall(rotation + 1 * dir, dist, WallStandardSize);
    CreateWall(rotation + 2 * dir, dist, WallStandardSize + hallwaySize / 4.0f);
    CreateWall(rotation + 3 * dir, dist, WallStandardSize + hallwaySize / 4.0f * 2.0f);
    CreateWall(rotation + 4 * dir, dist, WallStandardSize + hallwaySize / 4.0f * 3.0f);
    CreateWall(rotation + 5 * dir, dist, WallStandardSize + hallwaySize);

    dist += WallStandardSize + hallwaySize;
    CreateWall(rotation, dist);
    dist += distBetween;
    CreateWall(rotation + 1 * dir, dist);
    dist += distBetween;
    CreateWall(rotation + 2 * dir, dist);
    dist += distBetween;
    CreateWall(rotation + 3 * dir, dist);
    dist += distBetween;
    CreateWall(rotation + 4 * dir, dist);


    return hallwaySize + distBetween * 3 + StandardDistanceBetweenSets * 2;
}

// Wall Generator
typedef float (*WallPatternFunc)(int, float);
void UpdateWallGenerator(Entity& self) {
    if (Global::gameOver)
        return;

    // Create array of functions
    static const std::vector<WallPatternFunc> wallSets = {
        WallRing,
        WallGaps,
        MultiWallRing,
        MultiWallGaps,
        SpinAround
    };

    // Config
    static const float startDistance = 1.0f;
    static float delayTillNextSet = 0.5f;

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
