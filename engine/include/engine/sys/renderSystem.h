#pragma once

#include <engine/comp/text.h>
#include <engine/comp/sprite.h>
#include <engine/sys/_system.h>
#include <engine/sys/__oof.h>
#include <string>
#include <algorithm>
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

/**
 * @brief A struct that represents a colored character
 */
struct ColoredText {
    char character;
    Color color;
};

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

    /**
     * @brief Determines the alpha and color of a point
     * @details The alpha is calculated using the barycentric coordinates method
     * @param SpriteComponent The points of the triangle strip
     * @param x The x-coordinate of the point
     * @param y The y-coordinate of the point
     * @return A character representing the alpha of the point
     */
    static ColoredText AlphaColorOfPoint(Sprite &sprite, int x, int y);

    /**
     * @brief Sets a character at a position in the console
     * @param x The x-coordinate of the character
     * @param y The y-coordinate of the character
     * @param character The character to set
     */
    static void SetConsoleCharacter(int x, int y, ColoredText character);

    /**
     * @brief Draws a triangle to the console
     * @param triangleList The points of the triangle strip
     * @param index The index of the first point in the triangle strip
     */
    static void DrawTriangle(Sprite &sprite, int index);

    /**
     * @brief Draws text to the screen
     * @param text The text to draw
     * @param x The x-coordinate of the text
     * @param y The y-coordinate of the text
     */
    static void DrawTextToScreen(Text &text, int x, int y);
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
