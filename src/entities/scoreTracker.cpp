#include "scoreTracker.h"
#include "../global.h"
#include "../helper.h"
#include <engine/engine.h>
#include <engine/comp/script.h>
#include <engine/comp/depth.h>
#include <engine/sys/input.h>
#include <engine/sys/timeSystem.h>
#include <engine/sys/cameraSystem.h>
#include <engine/sys/audioSystem.h>

void UpdateScoreTracker(Entity &self) {
    // Define static variables
    static float deathZoomWaitTimer = 60;

    // Game Over
    if (Global::gameOver) {
        if (deathZoomWaitTimer > 0) {
            deathZoomWaitTimer -= TimeSystem::DeltaTime();
        }
    }

    // Remove all walls
    if (Global::gameOver && CameraSystem::zoom >= 4.5f and !Global::showGameOverUI) {
        Global::showGameOverUI = true;
        for(auto &entity : Engine::GetEntities("wall"))
            entity->Delete();
    }

    // Update Camera Zoom
    CameraSystem::zoom = ApproachEase(CameraSystem::zoom, (deathZoomWaitTimer <= 0) ? 5.0f : 1.0f, 0.5f, 0.8f);

    if (Global::gameOver && Input::GetKeyPressed(VK_ENTER)) {
        Global::gameOver = false;
        Global::showGameOverUI = false;
        Global::roundStart = TimeSystem::TimeRunning();
        AudioSystem::PlayAudio("audio/roundStart.wav", false, 0.2f);
        deathZoomWaitTimer = 60;
        for(auto &entity : Engine::GetEntities("wall"))
            entity->Delete();
    }
}

void CreateScoreTracker() {
    Engine::AddEntity(
        Depth(80),
        Script(UpdateScoreTracker)
    );
}
