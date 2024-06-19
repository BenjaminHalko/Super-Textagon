#include <engine/engine.h>
#include "entities/musicController.h"
#include "entities/background.h"
#include "entities/wallGenerator.h"
#include "entities/gameOver.h"
#include "entities/gui.h"
#include "entities/player.h"
#include "entities/core.h"

int main() {
    CreateMusicController();
    CreateBackground();
    CreateWallGenerator();
    CreateGameOverManager();
    CreateIntroGUI();

    Engine::GameLoop();
    return 0;
}
