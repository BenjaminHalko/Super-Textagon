#include "wall.h"
#include "../helper.h"
#include <engine/engine.h>
#include <engine/comp/depth.h>
#include <engine/comp/transform.h>
#include <engine/comp/sprite.h>
#include <engine/comp/script.h>
#include <engine/comp/collider.h>
#include <engine/comp/tag.h>
#include <engine/sys/timeSystem.h>

void UpdateWall(Entity& self) {
    // Config
    const float speed = 0.01f;

    // Define variables
    auto& scriptData = self.GetComponent<Script>();
    if (!scriptData.DataExists("baseSprite"))
        scriptData.SetData("baseSprite", Sprite(self.GetComponent<Sprite>()));
    auto& baseSprite = scriptData.GetData<Sprite>("baseSprite");
    auto& transform = self.GetComponent<Transform>();
    auto& sprite = self.GetComponent<Sprite>();

    // Update sprite
    for (auto& colouredPoint : baseSprite) {
        auto& point = colouredPoint.point;
        float dir = PointDirection(0, 0, point.x, point.y);
        float dist = PointDistance(0, 0, point.x, point.y) - speed * TimeSystem::DeltaTime();
        dist = (float)fmax(dist, 0.01f);

        point.x = LengthDir_x(dist, dir);
        point.y = LengthDir_y(dist, dir);
    }

    // Update Zoom
    ZoomSprite(sprite, baseSprite);

    // Update Collider
    auto& collider = self.GetComponent<Collider>();
    collider.Update(baseSprite);

    // Temp Create new wall
    if ((baseSprite.begin()+2)->point.x == 0.01f) {
        self.Delete();
        CreateWall((int) RandomRange(0, 5), 1.0f, RandomRange(0.3, 1));
    }
}

void CreateWall(int dir, float startDist, float size) {
    float alpha = (dir % 2 == 0) ? 1 : 0.9f;

    dir *= 60;

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
        Depth(-50),
        Script(UpdateWall),
        Transform(0, 0, 1, 1, (float)dir),
        Sprite(sprite),
        Collider(sprite)
    );
}

