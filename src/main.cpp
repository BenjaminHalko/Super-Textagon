#include <engine/engine.h>
#include "entities/_testEntity.h"
#include "entities/musicController.h"

int main() {
    CreateTestEntity();
    CreateMusicController();

    Engine::GameLoop();
    return 0;
}
