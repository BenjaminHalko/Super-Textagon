#include <engine/engine.h>
#include "entities/testEntity.h"

int main() {
    CreateTestEntity();

    Engine::GameLoop();
    return 0;
}
