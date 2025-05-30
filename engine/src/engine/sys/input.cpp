#include <engine/sys/input.h>
#include <unordered_map>

#ifdef _WIN32
#define NOVIRTUALKEYCODES
#include <windows.h>
#elif EMSCRIPTEN
#include <emscripten.h>
#endif

// Define the static variable
std::unordered_map<int, Input::KeyState> Input::_keys;

#ifdef __APPLE__
// List of keys to check on macOS
static const int macKeyList[] = {
    kVK_ANSI_A, kVK_ANSI_B, kVK_ANSI_C, kVK_ANSI_D, kVK_ANSI_E,
    kVK_ANSI_F, kVK_ANSI_G, kVK_ANSI_H, kVK_ANSI_I, kVK_ANSI_J,
    kVK_ANSI_K, kVK_ANSI_L, kVK_ANSI_M, kVK_ANSI_N, kVK_ANSI_O,
    kVK_ANSI_P, kVK_ANSI_Q, kVK_ANSI_R, kVK_ANSI_S, kVK_ANSI_T,
    kVK_ANSI_U, kVK_ANSI_V, kVK_ANSI_W, kVK_ANSI_X, kVK_ANSI_Y,
    kVK_ANSI_Z,
    kVK_Space, kVK_Return, kVK_Delete, kVK_Escape, kVK_Shift,
    kVK_Tab, kVK_PageUp, kVK_PageDown, kVK_Home, kVK_End,
    kVK_ForwardDelete, kVK_LeftArrow, kVK_RightArrow, kVK_UpArrow, kVK_DownArrow,
    kVK_ANSI_Keypad0, kVK_ANSI_Keypad1, kVK_ANSI_Keypad2, kVK_ANSI_Keypad3,
    kVK_ANSI_Keypad4, kVK_ANSI_Keypad5, kVK_ANSI_Keypad6, kVK_ANSI_Keypad7,
    kVK_ANSI_Keypad8, kVK_ANSI_Keypad9,
    kVK_ANSI_KeypadMultiply, kVK_ANSI_KeypadPlus, kVK_ANSI_KeypadMinus,
    kVK_ANSI_KeypadDecimal, kVK_ANSI_KeypadDivide,
    kVK_F1, kVK_F2, kVK_F3, kVK_F4, kVK_F5, kVK_F6,
    kVK_F7, kVK_F8, kVK_F9, kVK_F10, kVK_F11, kVK_F12
};
#endif

void Input::Init() {
#ifdef EMSCRIPTEN
    EM_ASM({
        if (!Module.keysDown) {
            Module.keysDown = {};
            document.addEventListener('keydown', function(event) {
                Module.keysDown[event.keyCode] = true;
                event.preventDefault();
            });
            document.addEventListener('keyup', function(event) {
                Module.keysDown[event.keyCode] = false;
                event.preventDefault();
            });
        }
    });
#endif
}

void Input::Clean() {
    _keys.clear();
}

void Input::Update() {
#ifdef _WIN32
    // Windows: Use GetAsyncKeyState to check key states
    for(int i = 0; i < 256; i++) {
        if(GetAsyncKeyState(i) & 0x8000) {
            if(_keys[i] == KeyState::UP)
                _keys[i] = KeyState::PRESSED;
            else
                _keys[i] = KeyState::HELD;
        } else {
            if (_keys[i] != KeyState::UP)
                _keys[i] = KeyState::UP;
        }
    }
#elif __APPLE__
    // macOS: Use CGEventSourceKeyState to check key states
    for (int keyCode : macKeyList) {
        bool isDown = CGEventSourceKeyState(kCGEventSourceStateHIDSystemState, keyCode);
        
        if (isDown) {
            if (_keys[keyCode] == KeyState::UP)
                _keys[keyCode] = KeyState::PRESSED;
            else
                _keys[keyCode] = KeyState::HELD;
        } else {
            if (_keys[keyCode] != KeyState::UP)
                _keys[keyCode] = KeyState::UP;
        }
    }
#elif EMSCRIPTEN
    // Emscripten: Use JavaScript to check key states
    for(int i = 0; i < 256; i++) {
        if(EM_ASM_INT({ return Module.keysDown[$0] ? 1 : 0; }, i)) {
            if(_keys[i] == KeyState::UP)
                _keys[i] = KeyState::PRESSED;
            else
                _keys[i] = KeyState::HELD;
        } else {
            if (_keys[i] != KeyState::UP)
                _keys[i] = KeyState::UP;
        }
    }
#endif
}

bool Input::GetKeyDown(int key) {
#ifdef __APPLE__
    // Convert ASCII codes to virtual key codes for macOS
    if (key >= 'A' && key <= 'Z') {
        key = kVK_ANSI_A + (key - 'A');
    } else if (key >= 'a' && key <= 'z') {
        key = kVK_ANSI_A + (key - 'a');
    }
#else
    if (key >= 'a' && key <= 'z')
        key -= 32;
#endif
    return _keys[key] != KeyState::UP;
}

bool Input::GetKeyPressed(int key) {
#ifdef __APPLE__
    // Convert ASCII codes to virtual key codes for macOS
    if (key >= 'A' && key <= 'Z') {
        key = kVK_ANSI_A + (key - 'A');
    } else if (key >= 'a' && key <= 'z') {
        key = kVK_ANSI_A + (key - 'a');
    }
#else
    if (key >= 'a' && key <= 'z')
        key -= 32;
#endif
    return _keys[key] == KeyState::PRESSED;
}
