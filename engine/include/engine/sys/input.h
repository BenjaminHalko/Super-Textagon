#pragma once

#ifdef __APPLE__
#include <Carbon/Carbon.h>
#endif

#include <engine/sys/_system.h>
#include <unordered_map>

#ifdef __APPLE__
    #define VK_BACK           kVK_Delete
    #define VK_TAB            kVK_Tab
    #define VK_ENTER          kVK_Return
    #define VK_SHIFT          kVK_Shift
    #define VK_ESCAPE         kVK_Escape
    #define VK_SPACE          kVK_Space
    #define VK_PRIOR          kVK_PageUp
    #define VK_NEXT           kVK_PageDown
    #define VK_END            kVK_End
    #define VK_HOME           kVK_Home
    #define VK_LEFT           kVK_LeftArrow
    #define VK_UP             kVK_UpArrow
    #define VK_RIGHT          kVK_RightArrow
    #define VK_DOWN           kVK_DownArrow
    #define VK_DELETE         kVK_ForwardDelete
    #define VK_NUMPAD0        kVK_ANSI_Keypad0
    #define VK_NUMPAD1        kVK_ANSI_Keypad1
    #define VK_NUMPAD2        kVK_ANSI_Keypad2
    #define VK_NUMPAD3        kVK_ANSI_Keypad3
    #define VK_NUMPAD4        kVK_ANSI_Keypad4
    #define VK_NUMPAD5        kVK_ANSI_Keypad5
    #define VK_NUMPAD6        kVK_ANSI_Keypad6
    #define VK_NUMPAD7        kVK_ANSI_Keypad7
    #define VK_NUMPAD8        kVK_ANSI_Keypad8
    #define VK_NUMPAD9        kVK_ANSI_Keypad9
    #define VK_MULTIPLY       kVK_ANSI_KeypadMultiply
    #define VK_ADD            kVK_ANSI_KeypadPlus
    #define VK_SEPARATOR      kVK_ANSI_Comma
    #define VK_SUBTRACT       kVK_ANSI_KeypadMinus
    #define VK_DECIMAL        kVK_ANSI_KeypadDecimal
    #define VK_DIVIDE         kVK_ANSI_KeypadDivide
    #define VK_F1             kVK_F1
    #define VK_F2             kVK_F2
    #define VK_F3             kVK_F3
    #define VK_F4             kVK_F4
    #define VK_F5             kVK_F5
    #define VK_F6             kVK_F6
    #define VK_F7             kVK_F7
    #define VK_F8             kVK_F8
    #define VK_F9             kVK_F9
    #define VK_F10            kVK_F10
    #define VK_F11            kVK_F11
    #define VK_F12            kVK_F12
#else
    #define VK_BACK           0x08
    #define VK_TAB            0x09
    #define VK_ENTER          0x0D
    #define VK_SHIFT          0x10
    #define VK_ESCAPE         0x1B
    #define VK_SPACE          0x20
    #define VK_PRIOR          0x21
    #define VK_NEXT           0x22
    #define VK_END            0x23
    #define VK_HOME           0x24
    #define VK_LEFT           0x25
    #define VK_UP             0x26
    #define VK_RIGHT          0x27
    #define VK_DOWN           0x28
    #define VK_DELETE         0x2E
    #define VK_NUMPAD0        0x60
    #define VK_NUMPAD1        0x61
    #define VK_NUMPAD2        0x62
    #define VK_NUMPAD3        0x63
    #define VK_NUMPAD4        0x64
    #define VK_NUMPAD5        0x65
    #define VK_NUMPAD6        0x66
    #define VK_NUMPAD7        0x67
    #define VK_NUMPAD8        0x68
    #define VK_NUMPAD9        0x69
    #define VK_MULTIPLY       0x6A
    #define VK_ADD            0x6B
    #define VK_SEPARATOR      0x6C
    #define VK_SUBTRACT       0x6D
    #define VK_DECIMAL        0x6E
    #define VK_DIVIDE         0x6F
    #define VK_F1             0x70
    #define VK_F2             0x71
    #define VK_F3             0x72
    #define VK_F4             0x73
    #define VK_F5             0x74
    #define VK_F6             0x75
    #define VK_F7             0x76
    #define VK_F8             0x77
    #define VK_F9             0x78
    #define VK_F10            0x79
    #define VK_F11            0x7A
    #define VK_F12            0x7B
#endif

/**
 * @brief The Input system is used to track the state of keys
 * @note This system should be used to check if a key is pressed
 * or held down
 */

class Input : public System {
    friend class Engine;
    enum KeyState {UP, PRESSED, HELD};
    static std::unordered_map<int, KeyState> _keys;

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
    static bool GetKeyDown(int key);

    /**
     * @brief Check if a key is pressed
     * @param key The key to check
     * @return bool True if the key is pressed
     */
    static bool GetKeyPressed(int key);
};
