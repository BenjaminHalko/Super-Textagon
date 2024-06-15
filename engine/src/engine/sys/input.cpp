#include <engine/sys/input.h>
#ifdef _WIN32
#define NOVIRTUALKEYCODES
#include <windows.h>
#else
#include <linux/input.h>
#include <fcntl.h>
#include <csignal>
#include <cstdlib>

#endif

// Define the static variable
std::unordered_map<int, Input::KeyState> Input::_keys;

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
    struct input_event ev{};
    int fd = open("/dev/input/eventX", O_RDONLY);
    if (fd == -1) {
        // Handle error
        exit(1);
        return;
    }

    while (read(fd, &ev, sizeof(struct input_event)) > 0) {
        if (ev.type == EV_KEY) {
            if (ev.value == 1) { // Key press
                if (_keys[ev.code] == KeyState::UP)
                    _keys[ev.code] = KeyState::PRESSED;
                else
                    _keys[ev.code] = KeyState::HELD;
            } else if (ev.value == 0) { // Key release
                _keys[ev.code] = KeyState::UP;
            }
        }
    }

    close(fd);
#endif
}

bool Input::GetKeyDown(int key) {
    return _keys[key] != KeyState::UP;
}

bool Input::GetKeyPressed(int key) {
    return _keys[key] == KeyState::PRESSED;
}
