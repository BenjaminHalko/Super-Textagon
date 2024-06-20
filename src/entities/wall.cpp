#include "wall.h"
#include "../helper.h"
#include "../global.h"
#include <engine/engine.h>
#include <engine/comp/depth.h>
#include <engine/comp/transform.h>
#include <engine/comp/sprite.h>
#include <engine/comp/script.h>
#include <engine/comp/collider.h>
#include <engine/comp/tag.h>
#include <engine/sys/timeSystem.h>
#include <engine/sys/cameraSystem.h>
#include <cmath>

void UpdateWall(Entity& self) {

    // Define variables
    auto &scriptData = self.GetComponent<Script>();
    if (!scriptData.DataExists("baseSprite"))
        scriptData.SetData("baseSprite", Sprite(self.GetComponent<Sprite>()));
    auto &baseSprite = scriptData.GetData<Sprite>("baseSprite");
    auto &sprite = self.GetComponent<Sprite>();

    // Update sprite
    if (!Global::gameOver) {
        for (auto &colouredPoint: baseSprite) {
            auto &point = colouredPoint.point;
            float dir = PointDirection(0, 0, point.x, point.y);
            float dist =
                    PointDistance(0, 0, point.x, point.y) - Global::wallSpd * TimeSystem::DeltaTime();
            dist = (float)fmax(dist, 0.01f);

            point.x = LengthDir_x(dist, dir);
            point.y = LengthDir_y(dist, dir);
        }
    }

    // Update Sprite Color
    for(auto &point : sprite)
        point.color = MergeColors(
            MakeColor(Global::lastHue, 1.0, point.alpha),
            MakeColor(Global::hue, 1.0, point.alpha),
            Global::hueShift
        );

    // Update Zoom
    if (Global::gameOver)
        ZoomSprite(sprite, baseSprite, Global::zoom + CameraSystem::zoom - 1.0f);
    else
        ZoomSprite(sprite, baseSprite);

    // Update Collider
    auto &collider = self.GetComponent<Collider>();
    collider.Update(baseSprite);

    // Delete wall
    if ((baseSprite.begin() + 2)->point.x == 0.01f) {
        self.Delete();
    }
}

void CreateWall(int dir, float startDist, float size) {
    float alpha = (dir % 2 == 0) ? 1 : 0.9f;

    dir *= 60;

    while (dir < 0)
        dir += 360;
    while (dir >= 360)
        dir -= 360;

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
        Tag("wall"),
        Depth(50),
        Script(UpdateWall),
        Transform(0, 0, 1, 1, (float)dir),
        Sprite(sprite),
        Collider(sprite)
    );
}

