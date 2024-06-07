#pragma once

#include <unordered_map>
#include "_system.h"

enum Key {
    LEFT = 0,
    RIGHT,
    QUIT
};

class Input : public System {
    enum KeyState {UP, PRESSED, HELD};
    static std::unordered_map<Key, KeyState> keys;
public:
    void Update() override;
    static bool GetKeyDown(Key key);
    static bool GetKeyPressed(Key key);
};
