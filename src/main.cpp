#include <engine/engine.h>
#include "entities/_testEntity.h"
#include "entities/musicController.h"
#include "entities/background.h"

int main() {
    CreateTestEntity();
    CreateMusicController();
    CreateBackground();

    Engine::GameLoop();
    return 0;
}
