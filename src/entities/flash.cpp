#include "flash.h"
#include <engine/engine.h>
#include <engine/comp/sprite.h>
#include <engine/comp/transform.h>
#include <engine/comp/depth.h>
#include <engine/comp/script.h>
#include <engine/sys/cameraSystem.h>
#include <engine/sys/timeSystem.h>

// Perform flash action (brighten screen)
void UpdateFlash(Entity& self) {
    auto &script = self.GetComponent<Script>();
    if (!script.DataExists("time"))
        script.SetData("time", 3.0f);
    script.SetData("time", script.GetData<float>("time") - TimeSystem::DeltaTime());
    if (script.GetData<float>("time") <= 0)
        self.Delete();
}

// Create flash effect (upon death)
void FlashScreen() {
    Engine::AddEntity(
        Depth(-1000),
        Sprite(1, 3, 0xFFFFFF, 1, 0xFFFFFF, 1),
        Transform(0, 0, CameraSystem::zoom, CameraSystem::zoom),
        Script(UpdateFlash)
    );
}
