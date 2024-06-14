#include <engine/sys/input.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <ncurses.h>
#endif

// Define the static variable
std::unordered_map<Key, Input::KeyState> Input::_keys;

#ifdef _WIN32
std::unordered_map<Key, int> Input::_keyMap = {
    {Key::LEFT, VK_LEFT},
    {Key::RIGHT, VK_RIGHT},
    {Key::ESCAPE, VK_ESCAPE}
};
#else
std::unordered_map<Key, int> Input::_keyMap {
    {Key::LEFT, KEY_LEFT},
    {Key::RIGHT, KEY_RIGHT},
    {Key::ESCAPE, 27}
};
#endif

void Input::Init() {
#ifndef _WIN32
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
#endif
}

void Input::Clean() {
#ifndef _WIN32
    endwin();
#endif
}

void Input::Update() {
    for(int i = 0; i <= (int)Key::ESCAPE; i++) {
        bool held;

        // Cast the integer to a key
        Key key = static_cast<Key>(i);



        // Check the key
#ifdef _WIN32
        held = GetAsyncKeyState(_keyMap[key]);
#else
        held = getch() == _keyMap[key];
#endif

        // Update the key state
        if (!held)
            _keys[key] = KeyState::UP;
        else if (_keys[key] == KeyState::UP)
            _keys[key] = KeyState::PRESSED;
        else
            _keys[key] = KeyState::HELD;
    }
}

bool Input::GetKeyDown(Key key) {
    return _keys[key] != KeyState::UP;
}

bool Input::GetKeyPressed(Key key) {
    return _keys[key] == KeyState::PRESSED;
}
