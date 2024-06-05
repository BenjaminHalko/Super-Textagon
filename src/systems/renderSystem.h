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
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

    // Buffer to store the console
    std::string consoleBuffer;
    int charCount = 0;

    /**
     * @brief Sets a character at a position in the console
     * @param x
     * @param y
     * @param c
     */
    void SetConsoleCharacter(int x, int y, char c) {
        if (x >= 0 && x < consoleInfo.dwSize.X && y >= 0 && y < consoleInfo.dwSize.Y)
            consoleBuffer[y * consoleInfo.dwSize.X + x] = c;
    }

    /**
     * @brief Draws a triangle to the console
     * @param triangleStrip The points of the triangle strip
     * @param index The index of the first point in the triangle strip
     * @param c The character to draw
     */
    void DrawTriangle(TriangleStrip &triangleStrip, int index, char c) {
        // Create a copy of the points
        TriangleStrip points(3);

        // Convert the points to screen space, from 0 to dwSize
        for (int i = index; i < index + 3; i++) {
            points[i].x = triangleStrip[i].x * consoleInfo.dwSize.X;
            points[i].y = triangleStrip[i].y * consoleInfo.dwSize.Y;
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
        for (int y = std::ceil(points[0].y); y <= std::floor(points[1].y); y++) {
            float x1 = points[0].x + slopeAC * (y - points[0].y);
            float x2 = points[0].x + slopeAB * (y - points[0].y);
            if (x1 > x2) std::swap(x1, x2); // Ensure x1 is always less than x2
            for (int x = std::ceil(x1); x <= std::floor(x2); x++) {
                SetConsoleCharacter(x, y, c);
            }
        }

        // Draw the lower part of the triangle (from B to C)
        for (int y = std::ceil(points[1].y); y <= std::floor(points[2].y); y++) {
            float x1 = points[0].x + slopeAC * (y - points[0].y);
            float x2 = points[1].x + slopeBC * (y - points[1].y);
            if (x1 > x2) std::swap(x1, x2); // Ensure x1 is always less than x2
            for (int x = std::ceil(x1); x <= std::floor(x2); x++) {
                SetConsoleCharacter(x, y, c);
            }
        }
    }

    /**
     * @brief Draws a triangle strip to the console
     * @param triangleStrip The points of the triangle strip
     * @param c The character to draw
     * @details For more info on a triangle strip, see https://en.wikipedia.org/wiki/Triangle_strip
     */
    void DrawTriangleStrip(TriangleStrip &triangleStrip, char c) {
        DrawTriangle(triangleStrip, 0, c);

    }
public:
    void UpdateEntity(Entity &entity) override {
        static int num = 0;
        num++;

        // the 0.5 is for displaying in the center, this will get changed...
        auto component = entity.GetComponent<SpriteComponent>();
        component.rotation = num;
        auto sprite = component.GetSprite(0.5f, 0.5f);


        DrawTriangleStrip(sprite, '#');
    }

    void PreUpdate() override {
        // Get the console info
        // consoleInfo.dwSize stores the amount of characters in the console
        GetConsoleScreenBufferInfo(hStdOut, &consoleInfo);

        // If the size of the console has changed, clear the console
        if (consoleInfo.dwSize.X * consoleInfo.dwSize.Y != charCount) {
            charCount = consoleInfo.dwSize.X * consoleInfo.dwSize.Y;
            system("cls");
        }

        // Create a string to store characters that will be drawn to the console
        consoleBuffer = std::string(charCount, ' ');
    }

    void PostUpdate() override {
        // Draw the console buffer
        std::cout << consoleBuffer;

        // Move cursor home
        SetConsoleCursorPosition(hStdOut, {0, 0});
    }
};
