#include "gameOver.h"
#include "flash.h"
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
    static float highScore = Load();
    static bool gotHighScore = false;

    // Game Over
    if (Global::gameOver) {
        if (deathZoomWaitTimer > 0) {
            deathZoomWaitTimer -= TimeSystem::DeltaTime();

            if (deathZoomWaitTimer <= 0) {
                for(auto &entity : Engine::GetEntities("GUI"))
                    entity->Delete();

                // Save High Score
                if (RoundRunning() > highScore) {
                    highScore = RoundRunning();
                    Save(highScore);
                }
            }
        }
    }

    // Remove all walls
    if (!Global::intro && Global::gameOver && CameraSystem::zoom >= 4.5f and !Global::showGameOverUI) {
        Global::showGameOverUI = true;
        for(auto &entity : Engine::GetEntities("wall"))
            entity->Delete();

        CreateGameOverGUI(highScore);
        AudioSystem::PlayAudio("audio/game_over.ogg", false, 1.0f);
    }

    // Update Camera Zoom
    if (Global::intro)
        CameraSystem::zoom = 5.0f;
    else
        CameraSystem::zoom = ApproachEase(CameraSystem::zoom, (deathZoomWaitTimer <= 0) ? 5.0f : 1.0f, 0.5f, 0.8f);

    if (Global::gameOver && (Input::GetKeyPressed(VK_ENTER) || Input::GetKeyPressed(VK_SHIFT) || Input::GetKeyPressed(VK_SPACE)) && TimeSystem::TimeRunning() > 0.5f) {
        for(auto &entity : Engine::GetEntities("GUI"))
            entity->Delete();
        for(auto &entity : Engine::GetEntities("wall"))
            entity->Delete();
        Global::gameOver = false;
        Global::showGameOverUI = false;
        gotHighScore = false;
        Global::roundStart = TimeSystem::TimeRunning();
        AudioSystem::PlayAudio("audio/roundStart.wav", false, 0.07f);
        AudioSystem::PlayAudio("audio/begin.ogg", false, 1.0f);
        deathZoomWaitTimer = 60;
        CreateGUI();

        if (Global::intro) {
            Global::intro = false;
            CreateCore();
            CreatePlayer();
            CameraSystem::zoom = 10.0f;
        }
    }

    // Check for high score
    if (RoundRunning() > highScore && !gotHighScore) {
        gotHighScore = true;
        if (highScore != 0) {
            AudioSystem::PlayAudio("audio/excellent.ogg", false, 1.0f);
            CreateNewRecord();
        }
    }

    // Quit Game
    if (Input::GetKeyPressed(VK_ESCAPE)) {
        if (!Global::gameOver) {
            Global::finalScore = RoundRunning();
            Global::gameOver = true;
            FlashScreen();
            AudioSystem::PlayAudio("audio/death.wav", false, 0.4f);
        } else {
            Engine::StopGame();
        }
    }

    // Erase high score
    if (Input::GetKeyPressed(VK_DELETE)) {
        highScore = 0;
        Save(highScore);
        AudioSystem::PlayAudio("audio/death.wav", false, 0.4f);
    }
}

void CreateGameOverManager() {
    Engine::AddEntity(
        Depth(80),
        Script(UpdateGameOverManager)
    );
}
