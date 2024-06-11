#include <engine/engine.h>
#include "entities/testEntity.h"

int main() {
    Engine::AddEntity<TestEntity>();
    Engine::GameLoop();
    return 0;
}
