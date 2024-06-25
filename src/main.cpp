#include <engine/engine.h>
#include "entities/background.h"
#include "entities/wallGenerator.h"
#include "entities/gameOver.h"
#include "entities/gui.h"

int main() {
    CreateBackground();
    CreateWallGenerator();
    CreateGameOverManager();
    CreateIntroGUI();

    Engine::RunGame();
    return 0;
}
