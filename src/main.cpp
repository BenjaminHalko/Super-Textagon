#include <engine/engine.h>
#include "entities/musicController.h"
#include "entities/background.h"
#include "entities/player.h"
#include "entities/core.h"
#include "entities/wall.h"

int main() {
    CreateMusicController();
    CreateBackground();
    CreateCore();
    CreatePlayer();
    CreateWall(0, 0.5f);
    CreateWall(1, 0.8f);

    Engine::GameLoop();
    return 0;
}
