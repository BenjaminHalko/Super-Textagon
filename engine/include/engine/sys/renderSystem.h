#pragma once

#include <engine/sys/_system.h>
#include <engine/comp/sprite.h>
#include <string>
#include <algorithm>
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

class RenderSystem : public System {
    // Handle to the console
    #ifdef _WIN32
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo{};
    #endif

    // Buffer to store the console
    std::vector<std::pair<char, Color>> consoleBuffer;
    int charCount = 0;
    int width = 0;
    int height = 0;

    // Queue screen clear
    bool clearScreen = false;

    // Draw color
    bool drawColor = true;

    /**
     * @brief Determines the alpha and color of a point
     * @details The alpha is calculated using the barycentric coordinates method
     * @param SpriteComponent The points of the triangle strip
     * @param x The x-coordinate of the point
     * @param y The y-coordinate of the point
     * @return A character representing the luminance of the point
     */
    std::pair<char, Color> AlphaColorOfPoint(Sprite &sprite, int x, int y);

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
    void DrawTriangle(Sprite &sprite, int index);
public:
    /**
     * @brief Initializes the render system
     */
    RenderSystem();

    /**
     * @brief Draws all the entities
     */
    void Update();
};
