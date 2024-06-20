#include <engine/engine.h>
#include "entities/background.h"
#include "entities/wallGenerator.h"
#include "entities/gameOver.h"
#include "entities/gui.h"
#include "entities/core.h"

int main() {
    CreateBackground();
    CreateWallGenerator();
    CreateGameOverManager();
    CreateIntroGUI();

    Engine::GameLoop();
    return 0;
}
