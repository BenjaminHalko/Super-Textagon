#include <engine/sys/renderSystem.h>
#include <engine/engine.h>
#include <engine/sys/transformSystem.h>
#include <engine/sys/spriteSystem.h>
#include <limits>
#include <cmath>
#include "engine/sys/input.h"

#ifndef _WIN32
#include <sys/ioctl.h>
#include <unistd.h>
#endif

RenderSystem::RenderSystem() {
#ifdef _WIN32
    // Disable scroll bars
    SetConsoleMode(hStdOut, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif

    // Disable the cursor
    std::cout << "\033[?25l";

    // Disable synchronous input
    std::ios::sync_with_stdio(false);

    // Untie cin and cout
    std::cin.tie(nullptr);
}

// Private

std::pair<char, Color> RenderSystem::AlphaColorOfPoint(SpriteComponent &sprite, int x, int y) {
    // Characters to use for alpha
    static const std::string alphaChars = ".`'^\",:;Il!i~+_-?][}{1)(|\\/*tjfrjxnvuczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@";
    static const int alphaCharsCount = (int)alphaChars.size();

    // Calculate the denominators for barycentric coordinates
    float denominator =
            (sprite[1].point.y - sprite[2].point.y) * (sprite[0].point.x - sprite[2].point.x) +
            (sprite[2].point.x - sprite[1].point.x) * (sprite[0].point.y - sprite[2].point.y);

    // Calculate barycentric coordinates
    float lambda1 = ((sprite[1].point.y - sprite[2].point.y) * ((float)x - sprite[2].point.x) + (sprite[2].point.x - sprite[1].point.x) * ((float)y - sprite[2].point.y)) / denominator;
    float lambda2 = ((sprite[2].point.y - sprite[0].point.y) * ((float)x - sprite[2].point.x) + (sprite[0].point.x - sprite[2].point.x) * ((float)y - sprite[2].point.y)) / denominator;
    float lambda3 = 1.0f - lambda1 - lambda2;

    // Calculate the alpha
    float alpha = lambda1 * sprite[0].alpha + lambda2 * sprite[1].alpha + lambda3 * sprite[2].alpha;

    // Calculate the character
    char character = alphaChars.at((int)((float)(alphaCharsCount-1) * alpha));

    if (drawColor) {
        // Calculate the color
        Color r = (int) (
                lambda1 * float(sprite[0].color >> 16 & 0xFF) +
                lambda2 * float(sprite[1].color >> 16 & 0xFF) +
                lambda3 * float(sprite[2].color >> 16 & 0xFF));
        Color g = (int) (
                lambda1 * float(sprite[0].color >> 8 & 0xFF) +
                lambda2 * float(sprite[1].color >> 8 & 0xFF) +
                lambda3 * float(sprite[2].color >> 8 & 0xFF));
        Color b = (int) (
                lambda1 * float(sprite[0].color & 0xFF) +
                lambda2 * float(sprite[1].color & 0xFF) +
                lambda3 * float(sprite[2].color & 0xFF));

        Color color = ((r << 16) | (g << 8) | b);

        // Return the character based on the luminance & color
        return {character, color};
    }

    // Return the character based on the alpha & color
    return {character, 0};
}

void RenderSystem::SetConsoleCharacter(int x, int y, std::pair<char, Color> character) {
    if (x >= 0 && x < width && y >= 0 && y < height)
        consoleBuffer[y * width + x] = character;
}

void RenderSystem::DrawTriangle(SpriteComponent& sprite, int index) {
    // Create a copy of the points
    SpriteComponent points(3);

    // Convert the points to screen space, from 0 to dwSize
    const float fontAspectRatio = 0.5f; // The x to y ratio of the font
    auto maxScreenSize = (float)fmax(width, (float)height / fontAspectRatio);

    for (int i = 0; i < 3; i++) {
        points[i].point.x = sprite[i + index].point.x * maxScreenSize + ((float)width - maxScreenSize) * 0.5f;
        points[i].point.y = sprite[i + index].point.y * maxScreenSize * fontAspectRatio + ((float)height - maxScreenSize * fontAspectRatio) * 0.5f;
        points[i].color = sprite[i + index].color;
        points[i].alpha = sprite[i + index].alpha;
    }

    // Sort the points by y-coordinate
    std::sort(points.begin(), points.end(), [](const ColoredPoint &a, const ColoredPoint &b) {
        return a.point.y < b.point.y;
    });

    // Calculate the slopes
    float slopeAC = (points[2].point.y - points[0].point.y == 0) ?
            std::numeric_limits<float>::infinity() : (points[2].point.x - points[0].point.x) / (points[2].point.y - points[0].point.y);
    float slopeBC = (points[2].point.y - points[1].point.y == 0) ?
            std::numeric_limits<float>::infinity() : (points[2].point.x - points[1].point.x) / (points[2].point.y - points[1].point.y);
    float slopeAB = (points[1].point.y - points[0].point.y == 0) ?
            std::numeric_limits<float>::infinity() : (points[1].point.x - points[0].point.x) / (points[1].point.y - points[0].point.y);

    // Draw the upper part of the triangle (from A to B)
    for (int y = (int)std::ceil(points[0].point.y); y <= (int)(points[1].point.y); y++) {
        float x1 = points[0].point.x + slopeAC * ((float)y - points[0].point.y);
        float x2 = points[0].point.x + slopeAB * ((float)y - points[0].point.y);
        if (x1 > x2) std::swap(x1, x2); // Ensure x1 is always less than x2
        for (int x = (int)std::ceil(x1); x <= (int)(x2); x++) {
            SetConsoleCharacter(x, y, AlphaColorOfPoint(points, x, y));
        }
    }

    // Draw the lower part of the triangle (from B to C)
    for (int y = (int)std::ceil(points[1].point.y); y <= (int)(points[2].point.y); y++) {
        float x1 = points[0].point.x + slopeAC * ((float)y - points[0].point.y);
        float x2 = points[1].point.x + slopeBC * ((float)y - points[1].point.y);
        if (x1 > x2) std::swap(x1, x2); // Ensure x1 is always less than x2
        for (int x = (int)std::ceil(x1); x <= (int)(x2); x++) {
            SetConsoleCharacter(x, y, AlphaColorOfPoint(points, x, y));
        }
    }
}

// Public

void RenderSystem::Update() {
    // Get the console info
#ifdef _WIN32
    GetConsoleScreenBufferInfo(hStdOut, &consoleInfo);
    width = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
    height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
#else
    struct winsize w{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    width = w.ws_col;
    height = w.ws_row;
#endif

    // If the size of the console has changed, clear the console
    if (width * height != charCount) {
        charCount = width * height;
        clearScreen = true;
    }

    // Resize the console buffer
    consoleBuffer = std::vector<std::pair<char, Color>>(charCount, {' ', 0});

    // Loop over all the entities
    for (auto &entity: Engine::GetEntities()) {

        // Check if the entity has a sprite component
        if (entity->HasComponents<SpriteComponent, TransformComponent>()) {

            auto entityTransformedSprite = TransformSystem::TransformSprite(
                    entity->GetComponent<SpriteComponent>(),
                    entity->GetComponent<TransformComponent>()
            );

            for (int i = 0; i < entityTransformedSprite.Size(); i += 3) {
                DrawTriangle(entityTransformedSprite, i);
            }
        }
    }

    // Clear the console
    if (clearScreen) {
#ifdef _WIN32
        system("cls");
#else
        std::cout << "\033[2J";
#endif
        clearScreen = false;
    }

    // Disable color
    if (Input::GetKeyPressed(Key::LEFT)) {
        drawColor = !drawColor;
    }

    // Draw the console buffer
    std::string stringToPrint;
    Color lastColor = 0;
    for(auto &character : consoleBuffer) {
        if (character.first == ' ') {
            stringToPrint += " ";
        } else {
            // The color code is in the format \033[38;2;r;g;bm
            if (drawColor && character.second != lastColor) {
                auto r = (character.second >> 16) & 0xFF;
                auto g = (character.second >> 8) & 0xFF;
                auto b = character.second & 0xFF;
                stringToPrint += "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
                lastColor = character.second;
            }
            stringToPrint += character.first;
        }
    }

    // Move the cursor to the top left
    stringToPrint += "\033[H\033[0m";

    // Print the string
    std::cout << stringToPrint;
}
