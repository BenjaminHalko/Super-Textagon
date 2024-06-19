#include <engine/engine.h>
#include "entities/musicController.h"
#include "entities/background.h"
#include "entities/player.h"
#include "entities/core.h"
#include "entities/wallGenerator.h"
#include "entities/scoreTracker.h"
#include "entities/gui.h"

int main() {
    CreateMusicController();
    CreateBackground();
    CreateCore();
    CreatePlayer();
    CreateWallGenerator();
    CreateScoreTracker();
    CreateGUI();

    Engine::GameLoop();
    return 0;
}
