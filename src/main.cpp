#include <engine/ecs.h>
#include "entities/testEntity.h"

int main() {
    ECS::AddEntity<TestEntity>();
    ECS::GameLoop();
    return 0;
}
