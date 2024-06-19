#include "gameOver.h"
#include "gui.h"
#include "player.h"
#include "core.h"
#include "../global.h"
#include "../helper.h"
#include <engine/engine.h>
#include <engine/comp/script.h>
#include <engine/comp/depth.h>
#include <engine/sys/input.h>
#include <engine/sys/timeSystem.h>
#include <engine/sys/cameraSystem.h>
#include <engine/sys/audioSystem.h>

void UpdateGameOverManager(Entity &self) {
    // Define static variables
    static float deathZoomWaitTimer = 0;

    // Game Over
    if (Global::gameOver) {
        if (deathZoomWaitTimer > 0) {
            deathZoomWaitTimer -= TimeSystem::DeltaTime();

            if (deathZoomWaitTimer <= 0) {
                for(auto &entity : Engine::GetEntities("GUI"))
                    entity->Delete();
            }
        }
    }

    // Remove all walls
    if (!Global::intro && Global::gameOver && CameraSystem::zoom >= 4.5f and !Global::showGameOverUI) {
        Global::showGameOverUI = true;
        for(auto &entity : Engine::GetEntities("wall"))
            entity->Delete();
    }

    // Update Camera Zoom
    if (Global::intro)
        CameraSystem::zoom = 5.0f;
    else
        CameraSystem::zoom = ApproachEase(CameraSystem::zoom, (deathZoomWaitTimer <= 0) ? 5.0f : 1.0f, 0.5f, 0.8f);

    if (Global::gameOver && Input::GetKeyPressed(VK_ENTER)) {
        for(auto &entity : Engine::GetEntities("GUI"))
            entity->Delete();
        Global::gameOver = false;
        Global::showGameOverUI = false;
        Global::roundStart = TimeSystem::TimeRunning();
        AudioSystem::PlayAudio("audio/roundStart.wav", false, 0.1f);
        deathZoomWaitTimer = 60;
        CreateGUI();

        if (Global::intro) {
            Global::intro = false;
            CreateCore();
            CreatePlayer();
        }
    }
}

void CreateGameOverManager() {
    Engine::AddEntity(
        Depth(80),
        Script(UpdateGameOverManager)
    );
}
