#include "_ecs/ecs.hpp"
#include "entities/testEntity.hpp"
#include "systems/renderSystem.hpp"

// ECS
// ECS::entities
   // Components
   // What systems need to be run
// ECS::systems
    // A function on how to manipulate the entities components
        // Gets looped over all entities, that use the system






int main() {
    ECS ecs;

    // Add Entities
    ecs.AddEntity<TestEntity>();

    // Add Systems
    ecs.AddSystem<RenderSystem>();

    // Step
    ecs.Step();

    return 0;
}
