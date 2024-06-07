#pragma once

#include "_system.h"
#include "../components/spriteComponent.h"
#include <string>
#include <windows.h>
#include <algorithm>
#include <iostream>

class RenderSystem : public System {
    // Handle to the console
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo{};

    // Buffer to store the console
    std::vector<std::pair<char, unsigned int>> consoleBuffer;
    int charCount = 0;

    // Queue screen clear
    bool clearScreen = false;

    static std::pair<char, Color> LumAndColorOfPoint(SpriteComponent &sprite, int x, int y);

    void SetConsoleCharacter(int x, int y, char character, unsigned int color);

    void DrawTriangle(SpriteComponent &sprite, int index);
public:
    RenderSystem();
    void Update() override;
};
