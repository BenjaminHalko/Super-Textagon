#include <engine/engine.h>
#include "entities/testEntity.h"

int main() {
    Engine::AddEntity<TestEntity>(0);
    Engine::AddEntity<TestEntity>(1);

    Engine::GameLoop();
    return 0;
}
