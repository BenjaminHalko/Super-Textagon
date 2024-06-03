#pragma once

#include <unordered_map>

enum Key {
    LEFT = 0,
    RIGHT,
    QUIT
};

class Input {
    enum KeyState {UP, PRESSED, HELD};
    static std::unordered_map<Key, KeyState> keys;
public:
    static void Update();
    static bool GetKeyDown(Key key);
    static bool GetKeyPressed(Key key);
};
