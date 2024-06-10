#pragma once

#include <engine/sys/_system.h>
#include <engine/comp/spriteComponent.h>
#include <string>
#include <windows.h>
#include <algorithm>
#include <iostream>

class RenderSystem : public System {
    // Handle to the console
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo{};

    // Buffer to store the console
    std::vector<std::pair<char, Color>> consoleBuffer;
    int charCount = 0;

    // Queue screen clear
    bool clearScreen = false;

    /**
     * @brief Determines the alpha and color of a point
     * @details The alpha is calculated using the barycentric coordinates method
     * @param SpriteComponent The points of the triangle strip
     * @param x The x-coordinate of the point
     * @param y The y-coordinate of the point
     * @return A character representing the luminance of the point
     */
    static std::pair<char, Color> AlphaColorOfPoint(SpriteComponent &sprite, int x, int y);

    /**
     * @brief Sets a character at a position in the console
     * @param x The x-coordinate of the character
     * @param y The y-coordinate of the character
     * @param character The character to set
     */
    void SetConsoleCharacter(int x, int y, std::pair<char, Color> character);

    /**
     * @brief Draws a triangle to the console
     * @param triangleList The points of the triangle strip
     * @param index The index of the first point in the triangle strip
     */
    void DrawTriangle(SpriteComponent &sprite, int index);
public:
    RenderSystem();
    void Update() override;
};
