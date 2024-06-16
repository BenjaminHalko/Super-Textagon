#pragma once

#include <engine/sys/_system.h>
#include <engine/sys/__oof.h>
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
    static HANDLE hStdOut;
    static CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    #endif

    // Buffer to store the console
    static oof::screen<std::string> consoleBuffer;
    static int charCount;
    static int width;
    static int height;

    // Queue screen clear
    static bool clearScreen;

    // Draw color
    static bool drawColor;

    /**
     * @brief Determines the alpha and color of a point
     * @details The alpha is calculated using the barycentric coordinates method
     * @param SpriteComponent The points of the triangle strip
     * @param x The x-coordinate of the point
     * @param y The y-coordinate of the point
     * @return A character representing the luminance of the point
     */
    static std::pair<char, Color> AlphaColorOfPoint(Sprite &sprite, int x, int y);

    /**
     * @brief Sets a character at a position in the console
     * @param x The x-coordinate of the character
     * @param y The y-coordinate of the character
     * @param character The character to set
     */
    static void SetConsoleCharacter(int x, int y, std::pair<char, Color> character);

    /**
     * @brief Draws a triangle to the console
     * @param triangleList The points of the triangle strip
     * @param index The index of the first point in the triangle strip
     */
    static void DrawTriangle(Sprite &sprite, int index);
public:
    /**
     * @brief Initializes the render system
     */
    static void Init();

    /**
     * @brief Draws all the entities
     */
    static void Update();
};
