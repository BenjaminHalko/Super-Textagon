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

float WallRing2Holes(int rotation, float dist) {
    CreateWall(rotation + 1, dist);
    CreateWall(rotation + 2, dist);
    CreateWall(rotation + 3, dist);
    CreateWall(rotation + 5, dist);
    return StandardDistanceBetweenSets;
}

// Wall patterns (Stores all existing patterns below)
float MultiWallRing(int rotation, float dist) {
    dist += WallRing(rotation, dist);
    dist += WallRing(rotation + 3, dist);
    WallRing(rotation, dist);
    return StandardDistanceBetweenSets * 3;
}

float MultiWallGaps(int rotation, float dist) {
    dist += WallGaps(rotation, dist);
    dist += WallGaps(rotation + 1, dist);
    WallGaps(rotation, dist);
    return StandardDistanceBetweenSets * 3;
}

// Spins wall to match with spinning background
float SpinAround(int rotation, float dist) {
    const float distBetween = WallStandardSize * 0.5f;
    int dir = (RandomRange(0, 2) > 1) ? 1 : -1;
    const float hallwaySize = WallStandardSize * 5.0f;

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

float TightGaps(int rotation, float dist) {
    dist += WallGaps(rotation, dist) / 1.5f;
    dist += WallGaps(rotation + 1, dist) / 1.5f;
    dist += WallGaps(rotation, dist) / 1.5f;
    dist += WallGaps(rotation + 1, dist) / 1.5f;
    dist += WallGaps(rotation, dist) / 1.5f;
    WallGaps(rotation + 1, dist);
    return StandardDistanceBetweenSets * 3;
}

float SideToSide(int rotation, float dist) {
    float gap = WallStandardSize * 5.0f;
    CreateWall(rotation, dist, gap * 3.0f + WallStandardSize);
    CreateWall(rotation+3, dist, gap * 3.0f + WallStandardSize);
    CreateWall(rotation+1, dist);
    CreateWall(rotation+4, dist);
    CreateWall(rotation+2, dist+gap);
    CreateWall(rotation+5, dist+gap);
    CreateWall(rotation+1, dist+gap*2.0f);
    CreateWall(rotation+4, dist+gap*2.0f);
    CreateWall(rotation+2, dist+gap*3.0f);
    CreateWall(rotation+5, dist+gap*3.0f);
    return gap * 3.0f + StandardDistanceBetweenSets;
}

float MoveSlowly(int rotation, float dist) {
    int dir = (RandomRange(0, 2) > 1) ? 1 : -1;
    dist += WallRing(rotation, dist) / 1.5f;
    dist += WallRing(rotation+1*dir, dist) / 1.5f;
    dist += WallRing(rotation+2*dir, dist) / 1.5f;
    dist += WallRing(rotation+3*dir, dist) / 1.5f;
    dist += WallRing(rotation+4*dir, dist) / 1.5f;
    WallRing(rotation+5*dir, dist);
    return StandardDistanceBetweenSets * 4;
}

// Wall Generator
typedef float (*WallPatternFunc)(int, float);
void UpdateWallGenerator(Entity& self) {
    // Config
    static const float startDistance = 1.0f;
    static float delayTillNextSet = -0.2f;
    static int lastShapePhase = 0;

    // Return if game over
    if (Global::gameOver) {
        delayTillNextSet = -0.2f;
        return;
    }

    // Check if the shape phase has changed
    if (lastShapePhase != GetShapePhase()) {
        lastShapePhase = GetShapePhase();
        if (lastShapePhase != 0)
            delayTillNextSet *= 1.5f;
        else
            delayTillNextSet = -0.2f;
    }

    // Create array of functions
    std::vector<WallPatternFunc> wallSets;
    if (RoundRunning() < 10) {
        wallSets = {
            WallRing,
            WallGaps,
            WallRing2Holes,
            MultiWallGaps,
            MultiWallRing
        };
    } else if (RoundRunning() < 20) {
        wallSets = {
            WallRing,
            MultiWallRing,
            MultiWallGaps,
            SpinAround,
            SideToSide
        };
    } else {
        wallSets = {
            MultiWallRing,
            MultiWallGaps,
            SpinAround,
            TightGaps,
            MoveSlowly
        };
    }

    // Create new set
    delayTillNextSet -= TimeSystem::DeltaTime() * Global::wallSpd;

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
