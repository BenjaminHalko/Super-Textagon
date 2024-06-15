#include <engine/sys/input.h>
#ifdef _WIN32
#define NOVIRTUALKEYCODES
#include <windows.h>
#else
#include <ncurses.h>
#endif

// Define the static variable
std::unordered_map<int, Input::KeyState> Input::_keys;

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
#ifdef _WIN32
    for(int i = 0; i < 256; i++) {
        if(GetAsyncKeyState(i) & 0x8000) {
            if(_keys[i] == KeyState::UP)
                _keys[i] = KeyState::PRESSED;
            else
                _keys[i] = KeyState::HELD;
        } else {
            _keys[i] = KeyState::UP;
        }
    }
#else
    std::unordered_map<unsigned int, KeyState> tempKeys;
    while(int key = getch() != ERR) {
        if(_keys[key] == KeyState::UP)
            tempKeys[key] = KeyState::PRESSED;
        else
            tempKeys[key] = KeyState::HELD;

    }
    for(auto &key : _keys) {
        if(tempKeys.find(key.first) == tempKeys.end())
            key.second = KeyState::UP;
        else
            key.second = tempKeys[key.first];
    }
#endif
}

bool Input::GetKeyDown(int key) {
    if (key >= 'a' && key <= 'z')
        key -= 32;
    return _keys[key] != KeyState::UP;
}

bool Input::GetKeyPressed(int key) {
    if (key >= 'a' && key <= 'z')
        key -= 32;
    return _keys[key] == KeyState::PRESSED;
}
