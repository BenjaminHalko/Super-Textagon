#include "input.h"
#include <windows.h>

// Define the static variable
std::unordered_map<Key, Input::KeyState> Input::keys;

/**
 * @brief Loops over all the keys and tracks their state
 * @note This function should be called once per frame
 * to update the key states for the current frame
 */
void Input::Update() {
    for(int i = Key::LEFT; i <= Key::QUIT; i++) {
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
        if (!held)
            keys[key] = KeyState::UP;
        else if (keys[key] == KeyState::UP)
            keys[key] = KeyState::PRESSED;
        else
            keys[key] = KeyState::HELD;
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
