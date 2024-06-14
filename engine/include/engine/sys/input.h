#pragma once

#include <engine/sys/_system.h>
#include <unordered_map>


enum class Key {
    LEFT = 0,
    RIGHT,
    ESCAPE
};

/**
 * @brief The Input system is used to track the state of keys
 * @note This system should be used to check if a key is pressed
 * or held down
 */

class Input : public System {
    friend class Engine;
    enum KeyState {UP, PRESSED, HELD};
    static std::unordered_map<Key, KeyState> _keys;
    static std::unordered_map<Key, int> _keyMap;

    static void Init();
    static void Clean();

    /**
     * @brief Loops over all the keys and tracks their state
     * @note This function should be called once per frame
     * to update the key states for the current frame
     */
    static void Update();
public:
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
