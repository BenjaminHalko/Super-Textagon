#include "ecs.h"
#include "systems/input.h"

#include <chrono>
#include <thread>

// ECS
// ECS::entities
   // Components
   // What systems need to be run
// ECS::systems
    // A function on how to manipulate the entities components
        // Gets looped over all entities, that use the system

/**
 * @brief The main game loop
 */
void GameLoop() {
    const auto timeStep = std::chrono::milliseconds(1000 / 60);
    do {
        // Start the timer
        auto start = std::chrono::high_resolution_clock::now();

        // Update the entities
        ECS::Update();

        // Sleep for the remaining time
        std::this_thread::sleep_until(start + timeStep);
    } while(!Input::GetKeyPressed(Key::QUIT));
}

int main() {
    // Game Loop
    GameLoop();

    return 0;
}
