#include <iostream>

#include "ecs.hpp"
#include "entities/testEntity.hpp"



int main() {
    // Add Entities
    ECS::AddEntity<TestEntity>();

    return 0;
}
