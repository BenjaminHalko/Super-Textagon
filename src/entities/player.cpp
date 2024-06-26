#include "player.h"
#include "flash.h"
#include "../helper.h"
#include "../global.h"
#include <engine/engine.h>
#include <engine/comp/depth.h>
#include <engine/comp/transform.h>
#include <engine/comp/sprite.h>
#include <engine/comp/script.h>
#include <engine/comp/collider.h>
#include <engine/comp/tag.h>
#include <engine/sys/input.h>
#include <engine/sys/timeSystem.h>
#include <engine/sys/collisionSystem.h>
#include <engine/sys/cameraSystem.h>
#include <engine/sys/audioSystem.h>

// Updates player entity
void PlayerUpdate(Entity& self) {
    // Static variables
    static auto originalSprite = self.GetComponent<Sprite>();
    static auto &collider = self.GetComponent<Collider>();
    static auto &sprite = self.GetComponent<Sprite>();
    static auto &transform = self.GetComponent<Transform>();

    // While the game is still running...
    if (!Global::gameOver) {
        // Check for inputs, and apply to player direction
        bool left = Input::GetKeyDown(VK_LEFT) || Input::GetKeyDown('A');
        bool right = Input::GetKeyDown(VK_RIGHT) || Input::GetKeyDown('D');
        int dir = right - left;

        // Move Based on Input
        auto startRotation = transform.rotation;
        auto rotationSpd = (float) dir * Global::playerSpd * TimeSystem::DeltaTime();
        transform.rotation += rotationSpd;

        // Keep rotation between 0 and 360
        while (transform.rotation < 0)
            transform.rotation += 360;
        while (transform.rotation >= 360)
            transform.rotation -= 360;

        // Check for collision
        for (auto &entity: Engine::GetEntities("wall")) {
            if (CollisionSystem::CheckCollision(self, *entity)) {
                // Really complicated calculation for colliding with walls
                if (dir != 0) {
                    if (transform.rotation != floor(transform.rotation / 60) * 60) {
                        transform.rotation = floor(transform.rotation / 60) * 60;
                        if (dir < 0)
                            transform.rotation += 60;
                    }
                    transform.rotation -= (float) dir;
                }

                // Check for death :(
                // Check if the player is still alive
                for (auto &entity2: Engine::GetEntities("wall")) {
                    // Kill the player (clashing screen)
                    if (CollisionSystem::CheckCollision(self, *entity2)) {
                        transform.rotation = startRotation + rotationSpd * (float) dir;
                        Global::finalScore = RoundRunning();
                        Global::gameOver = true;
                        FlashScreen();
                        AudioSystem::PlayAudio("audio/death.wav", false, 0.3f);
                        break;
                    }
                }

                // Break out of the loop
                if (Global::gameOver)
                    break;
            }
        }

        // Safety Kill
        if (TimeSystem::DeltaTime() >= 100.0f) {
            Global::finalScore = 0.0f;
            Global::gameOver = true;
            FlashScreen();
            AudioSystem::PlayAudio("audio/death.wav", false, 0.3f);
        }
    }

    // Update Sprite
    transform.x_scale = 1 / (1.0f + (CameraSystem::zoom - 1.0f) * 0.5f);
    transform.y_scale = transform.x_scale;
    transform.x = LengthDir_x((CameraSystem::zoom - 1.0f) * 0.007f, transform.rotation);
    transform.y = LengthDir_y((CameraSystem::zoom - 1.0f) * 0.007f, transform.rotation);

    // Update Zoom
    ZoomSprite(sprite, originalSprite, Global::zoom);
}

// Create Player entity
void CreatePlayer() {
    const float xOffset = 0.055f;
    const float size = 0.015f;
    Sprite sprite{
        {{xOffset + size, 0}, 0xFFFFFF, 1},
        {{xOffset + LengthDir_x(size, 120), LengthDir_y(size, 120)}, 0xAAAAAA, 0.9f},
        {{xOffset + LengthDir_x(size, 240), LengthDir_y(size, 240)}, 0xAAAAAA, 0.9f}
    };

    Engine::AddEntity(
        Tag("player"),
        Depth(0),
        Transform(0, 0, 1, 1, 30),
        Sprite(sprite),
        Collider({sprite[0].point}),
        Script(PlayerUpdate)
    );
}
