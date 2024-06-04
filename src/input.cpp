#include "input.h"
#include "debug.h"
#include <set>

// Define the static variable
std::unordered_map<Key, Input::KeyState> Input::keys;

/**
 * @brief Loops over all the keys and tracks their state
 * @note This function should be called once per frame
 * to update the key states for the current frame
 */
void Input::Update() {
    std::set<Key> keysHeld;

    // Loop over all the keys and check if they are held
    int ch = getch();

    if (ch == ERR) {
        keys = {
            {Key::LEFT, KeyState::UP},
            {Key::RIGHT, KeyState::UP},
            {Key::QUIT, KeyState::UP}
        };
        return;
    }

    while (ch != ERR) {
        // Get the key
        switch (ch) {
            case KEY_LEFT:
                keysHeld.insert(Key::LEFT);
                break;
            case KEY_RIGHT:
                keysHeld.insert(Key::RIGHT);
                break;
            case 'q':
                keysHeld.insert(Key::QUIT);
                break;
            default:
                break;
        }

        ch = getch();
    }

    // Loop over all the keys and update their state
    for(int i = Key::LEFT; i <= Key::QUIT; i++) {
        Key key = static_cast<Key>(i);
        if (keysHeld.count(key) > 0) {
            if (keys[key] == KeyState::UP)
                keys[key] = KeyState::PRESSED;
            else
                keys[key] = KeyState::HELD;
        }
    }
}

/**
 * @brief Check if a key is held down
 * @param key The key to check
 * @return bool True if the key is held
 */
bool Input::GetKeyDown(Key key) {
    return keys[key] != KeyState::UP;
}

 /**
 * @brief Check if a key is pressed
 * @param key The key to check
 * @return bool True if the key is pressed
 */
bool Input::GetKeyPressed(Key key) {
    return keys[key] == KeyState::PRESSED;
}

/*
 * for(int i = Key::LEFT; i <= Key::QUIT; i++) {
        bool held;

        // Cast the integer to a key
        Key key = static_cast<Key>(i);

        // Check the key
        switch (key) {
            case Key::LEFT:
                held = GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A');
                break;
            case Key::RIGHT:
                held = GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D');
                break;
            case Key::QUIT:
                held = GetAsyncKeyState(VK_ESCAPE);
                break;
        }

        // Update the key state
        Print("Key: " + std::to_string(i) + " Held: " + std::to_string(held));
        if (!held)
            keys[key] = KeyState::UP;
        else if (keys[key] == KeyState::UP)
            keys[key] = KeyState::PRESSED;
        else
            keys[key] = KeyState::HELD;
    }
 */

/*
 *  Print("Test");

 */