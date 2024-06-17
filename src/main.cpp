#include <engine/engine.h>
#include "entities/musicController.h"
#include "entities/background.h"
#include "entities/player.h"
#include "entities/core.h"

int main() {
    CreateMusicController();
    CreateBackground();
    CreateCore();
    CreatePlayer();

    Engine::GameLoop();
    return 0;
}
