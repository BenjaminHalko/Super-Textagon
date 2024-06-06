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
    std::vector<std::pair<char, Color>> consoleBuffer;
    int charCount = 0;

    // Queue screen clear
    bool clearScreen = false;

    /**
     * @brief Determines the luminance of a point
     * @details The luminance is calculated using the barycentric coordinates method
     * @param TriangleList The points of the triangle strip
     * @param x The x-coordinate of the point
     * @param y The y-coordinate of the point
     * @return A character representing the luminance of the point
     */
    static std::pair<char, Color> LumAndColorOfPoint(TriangleList &points, int x, int y) {
        // Characters to use for luminance
        static const std::string lumChars = ".`'^\",:;Il!i~+_-?][}{1)(|\\/*tjfrjxnvuczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@";
        static const int lumCharsCount = (int)lumChars.size();

        // Calculate the denominators for barycentric coordinates
        float denominator = (points[1].y - points[2].y) * (points[0].x - points[2].x) + (points[2].x - points[1].x) * (points[0].y - points[2].y);

        // Calculate barycentric coordinates
        float lambda1 = ((points[1].y - points[2].y) * ((float)x - points[2].x) + (points[2].x - points[1].x) * ((float)y - points[2].y)) / denominator;
        float lambda2 = ((points[2].y - points[0].y) * ((float)x - points[2].x) + (points[0].x - points[2].x) * ((float)y - points[2].y)) / denominator;
        float lambda3 = 1.0f - lambda1 - lambda2;

        // Calculate the luminance
        float lum = lambda1 * points[0].luminance + lambda2 * points[1].luminance + lambda3 * points[2].luminance;

        // Calculate the color
        int r = (int)(lambda1 * float(points[0].color & 0xFF) + lambda2 * float(points[1].color & 0xFF) + lambda3 * float(points[2].color & 0xFF));
        int g = (int)(lambda1 * float(points[0].color >> 8 & 0xFF) + lambda2 * float(points[1].color >> 8 & 0xFF) + lambda3 * float(points[2].color >> 8 & 0xFF));
        int b = (int)(lambda1 * float(points[0].color >> 16 & 0xFF) + lambda2 * float(points[1].color >> 16 & 0xFF) + lambda3 * float(points[2].color >> 16 & 0xFF));

        // Calculate the color
        auto color = (Color)(r | (g << 8) | (b << 16));

        // Return the character based on the luminance & color
        return {lumChars.at((int)((float)(lumCharsCount-1) * lum)), color};
    }

    /**
     * @brief Sets a character at a position in the console
     * @param x The x-coordinate of the character
     * @param y The y-coordinate of the character
     * @param character The character to set
     * @param color The color to set
     */
    void SetConsoleCharacter(int x, int y, char character, Color color) {
        if (x >= 0 && x < consoleInfo.dwSize.X && y >= 0 && y < consoleInfo.dwSize.Y)
            consoleBuffer[y * consoleInfo.dwSize.X + x] = {character, color};
    }

    /**
     * @brief Draws a triangle to the console
     * @param triangleList The points of the triangle strip
     * @param index The index of the first point in the triangle strip
     */
    void DrawTriangle(TriangleList &triangleList, int index) {
        // Create a copy of the points
        TriangleList points(3);

        // Convert the points to screen space, from 0 to dwSize
        const float fontAspectRatio = 0.5f; // The x to y ratio of the font
        float maxScreenSize = max(consoleInfo.dwSize.X, consoleInfo.dwSize.Y / fontAspectRatio);

        for (int i = index; i < index + 3; i++) {
            points[i - index].x = triangleList[i].x * maxScreenSize + ((float)consoleInfo.dwSize.X - maxScreenSize) * 0.5f;
            points[i - index].y = triangleList[i].y * maxScreenSize * fontAspectRatio + ((float)consoleInfo.dwSize.Y - maxScreenSize * fontAspectRatio) * 0.5f;
            points[i - index].luminance = triangleList[i].luminance;
            points[i - index].color = triangleList[i].color;
        }

        // Sort the points by y-coordinate
        std::sort(points.begin(), points.end(), [](const Point &a, const Point &b) {
            return a.y < b.y;
        });

        // Calculate the slopes
        float slopeAC = (points[2].y - points[0].y == 0) ? std::numeric_limits<float>::infinity() : (points[2].x - points[0].x) / (points[2].y - points[0].y);
        float slopeBC = (points[2].y - points[1].y == 0) ? std::numeric_limits<float>::infinity() : (points[2].x - points[1].x) / (points[2].y - points[1].y);
        float slopeAB = (points[1].y - points[0].y == 0) ? std::numeric_limits<float>::infinity() : (points[1].x - points[0].x) / (points[1].y - points[0].y);

        // Draw the upper part of the triangle (from A to B)
        for (int y = (int)std::ceil(points[0].y); y <= (int)(points[1].y); y++) {
            float x1 = points[0].x + slopeAC * ((float)y - points[0].y);
            float x2 = points[0].x + slopeAB * ((float)y - points[0].y);
            if (x1 > x2) std::swap(x1, x2); // Ensure x1 is always less than x2
            for (int x = (int)std::ceil(x1); x <= (int)(x2); x++) {
                auto lumAndColor = LumAndColorOfPoint(points, x, y);
                SetConsoleCharacter(x, y, lumAndColor.first, lumAndColor.second);
            }
        }

        // Draw the lower part of the triangle (from B to C)
        for (int y = (int)std::ceil(points[1].y); y <= (int)(points[2].y); y++) {
            float x1 = points[0].x + slopeAC * ((float)y - points[0].y);
            float x2 = points[1].x + slopeBC * ((float)y - points[1].y);
            if (x1 > x2) std::swap(x1, x2); // Ensure x1 is always less than x2
            for (int x = (int)std::ceil(x1); x <= (int)(x2); x++) {
                auto lumAndColor = LumAndColorOfPoint(points, x, y);
                SetConsoleCharacter(x, y, lumAndColor.first, lumAndColor.second);
            }
        }
    }

    /**
     * @brief Draws a triangle strip to the console
     * @param triangleList The points of the triangle strip
     */
    void DrawTriangleList(TriangleList &triangleList) {
        for (int i = 0; i < triangleList.size() - 2; i += 3)
            DrawTriangle(triangleList, i);
    }
public:
    RenderSystem() {
        // Disable the cursor
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hStdOut, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(hStdOut, &cursorInfo);

        // Disable scroll bars
        SetConsoleMode(hStdOut, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

        // Disable synchronous input
        std::ios::sync_with_stdio(false);

        // Set the console mode to enable virtual terminal processing
        DWORD mode = 0;
        GetConsoleMode(hStdOut, &mode);
        mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hStdOut, mode);

        // Enable unit buffering
        std::cout << std::unitbuf;
    }

    void UpdateEntity(Entity &entity) override {
        static float num = 0;
        num++;

        // the 0.5 is for displaying in the center, this will get changed...
        auto component = entity.GetComponent<SpriteComponent>();
        component.rotation = (float)num;
        auto sprite = component.GetSprite(0.5f, 0.5f);


        DrawTriangleList(sprite);
    }

    void PreUpdate() override {
        // Get the console info
        // consoleInfo.dwSize stores the amount of characters in the console
        GetConsoleScreenBufferInfo(hStdOut, &consoleInfo);

        // If the size of the console has changed, clear the console
        if (consoleInfo.dwSize.X * consoleInfo.dwSize.Y != charCount) {
            charCount = consoleInfo.dwSize.X * consoleInfo.dwSize.Y;
            clearScreen = true;
        }

        // Resize the console buffer
        consoleBuffer = std::vector<std::pair<char, Color>>(charCount, {' ', 0});
    }

    void PostUpdate() override {
        // Clear the console
        if (clearScreen) {
            system("cls");
            clearScreen = false;
        }

        // Draw the console buffer
        std::string stringToPrint;
        for(auto &character : consoleBuffer) {
            if (character.first == ' ') {
                stringToPrint += " ";
            } else {
                auto r = character.second & 0xFF;
                auto g = (character.second >> 8) & 0xFF;
                auto b = (character.second >> 16) & 0xFF;
                std::string color = "\033[38;2;" + std::to_string(b) + ";" + std::to_string(g) + ";" + std::to_string(r) + "m";
                stringToPrint += color + character.first;
            }
        }
        std::cout << stringToPrint;

        // Move cursor home
        SetConsoleCursorPosition(hStdOut, {0, 0});
    }
};
