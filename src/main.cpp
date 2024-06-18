#include <engine/engine.h>
#include "entities/musicController.h"
#include "entities/background.h"
#include "entities/player.h"
#include "entities/core.h"
#include "entities/wallGenerator.h"

int main() {
    CreateMusicController();
    CreateBackground();
    CreateCore();
    CreatePlayer();
    CreateWallGenerator();

    Engine::GameLoop();
    return 0;
}
