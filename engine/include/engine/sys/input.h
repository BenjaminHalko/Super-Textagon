#pragma once

#include <engine/sys/_system.h>
#include <unordered_map>

enum Key {
    LEFT = 0,
    RIGHT,
    QUIT
};

class Input : public System {
    enum KeyState {UP, PRESSED, HELD};
    static std::unordered_map<Key, KeyState> keys;
public:
    /**
     * @brief Loops over all the keys and tracks their state
     * @note This function should be called once per frame
     * to update the key states for the current frame
     */
    void Update() override;

    /**
     * @brief Check if a key is held down
     * @param key The key to check
     * @return bool True if the key is held
     */
    static bool GetKeyDown(Key key);

    /**
     * @brief Check if a key is pressed
     * @param key The key to check
     * @return bool True if the key is pressed
     */
    static bool GetKeyPressed(Key key);
};
