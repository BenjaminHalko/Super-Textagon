#include <engine/engine.h>
#include <engine/comp/transform.h>
#include <engine/sys/renderSystem.h>
#include <engine/sys/transformSystem.h>
#include <engine/sys/cameraSystem.h>
#include <limits>
#include <cmath>
#ifdef EMSCRIPTEN
#include <emscripten.h>
#include "engine/sys/timeSystem.h"
#elif !_WIN32
#include <sys/ioctl.h>
#include <unistd.h>
#endif

// Define the static variables
#ifdef _WIN32
HANDLE RenderSystem::hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO RenderSystem::consoleInfo;
#endif
oof::screen<std::string> RenderSystem::consoleBuffer{0, 0, ' '};
int RenderSystem::charCount = 0;
int RenderSystem::width = 0;
int RenderSystem::height = 0;
bool RenderSystem::clearScreen = true;

// Render System
void RenderSystem::Init() {
#ifdef _WIN32
    // Disable scroll bars
    SetConsoleMode(hStdOut, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#elif EMSCRIPTEN
    EM_ASM({
        function setSize() {
            // Get the width of the viewport in pixels
            const viewportWidthInPixels = document.documentElement.clientWidth;
            const viewportHeightInPixels = document.documentElement.clientHeight;

            // Create a temporary element to measure character size
            const tempElement = document.createElement('span');
            tempElement.style.font = 'inherit'; // Use the current font
            tempElement.style.visibility = 'hidden'; // Ensure it doesn't affect the layout
            tempElement.innerHTML = 'MMMMMMMMMMMMMMMMMMMM'; // Use a typical character
            for(let i = 1; i < 20; i++)
                tempElement.innerHTML += '<br>MMMMMMMMMMMMMMMMMMMM'; // Use a typical character
            document.body.appendChild(tempElement);

            // Get the size of a single character
            const characterWidthInPixels = tempElement.offsetWidth / 20;
            const characterHeightInPixels = tempElement.offsetHeight / 20;

            console.log(characterWidthInPixels, characterHeightInPixels);

            // Remove the temporary element
            document.body.removeChild(tempElement);

            // Calculate the number of characters that fit in the viewport
            Module.width = Math.floor(viewportWidthInPixels / characterWidthInPixels);
            Module.height = Math.floor(viewportHeightInPixels / characterHeightInPixels);
        }
        window.addEventListener('resize', setSize);
        setSize();
        setTimeout(setSize, 100);
    });
#endif

#ifndef EMSCRIPTEN
    // Disable the cursor
    std::cout << "\033[?25l";

    // Disable synchronous input
    std::ios::sync_with_stdio(false);

    // Untie cin and cout
    std::cin.tie(nullptr);
#endif
}

// Private

ColoredText RenderSystem::AlphaColorOfPoint(Sprite &sprite, int x, int y) {
    // Characters to use for alpha
    static const std::string alphaChars = ".`'^\",:;Il!i~+_-?][}{1)(|\\/*tjfrjxnvuczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@";
    static const int alphaCharsCount = (int)alphaChars.size();

    // Check what needs checking
    bool gradientColor = sprite[0].color != sprite[1].color || sprite[1].color != sprite[2].color || sprite[0].color != sprite[2].color;
    bool gradientAlpha = sprite[0].alpha != sprite[1].alpha || sprite[1].alpha != sprite[2].alpha || sprite[0].alpha != sprite[2].alpha;

    // Exit early if no gradient
    if (!gradientColor && !gradientAlpha) {
        return {alphaChars.at((int)((float)(alphaCharsCount-1) * sprite[0].alpha)), sprite[0].color};
    }

    // Default values
    Color color = sprite[0].color;
    float alpha = sprite.alpha;

    // Calculate the denominators for barycentric coordinates
    float denominator =
            (sprite[1].point.y - sprite[2].point.y) * (sprite[0].point.x - sprite[2].point.x) +
            (sprite[2].point.x - sprite[1].point.x) * (sprite[0].point.y - sprite[2].point.y);

    // Calculate barycentric coordinates
    float lambda1 = ((sprite[1].point.y - sprite[2].point.y) * ((float)x - sprite[2].point.x) + (sprite[2].point.x - sprite[1].point.x) * ((float)y - sprite[2].point.y)) / denominator;
    float lambda2 = ((sprite[2].point.y - sprite[0].point.y) * ((float)x - sprite[2].point.x) + (sprite[0].point.x - sprite[2].point.x) * ((float)y - sprite[2].point.y)) / denominator;
    float lambda3 = 1.0f - lambda1 - lambda2;

    if (gradientAlpha) {
        // Calculate the alpha
        alpha = lambda1 * sprite[0].alpha + lambda2 * sprite[1].alpha + lambda3 * sprite[2].alpha;
        alpha *= sprite.alpha;

        // Clamp the alpha
        alpha = (float) fmax(0, fmin(1, alpha));
    }

    // Calculate the character
    char character = alphaChars.at((int) ((float) (alphaCharsCount - 1) * alpha));

    if (gradientColor) {
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

        color = ((r << 16) | (g << 8) | b);
    }

    // Merge the colour
    if (sprite.tintAlpha != 0) {
        Color r = int(float(color >> 16 & 0xFF) * (1 - sprite.tintAlpha));
        Color g = int(float(color >> 8 & 0xFF) * (1 - sprite.tintAlpha));
        Color b = int(float(color & 0xFF) * (1 - sprite.tintAlpha));

        float tintR = (float(sprite.tint >> 16 & 0xFF) * sprite.tintAlpha);
        float tintG = (float(sprite.tint >> 8 & 0xFF) * sprite.tintAlpha);
        float tintB = (float(sprite.tint & 0xFF) * sprite.tintAlpha);

        r = (int) (float(r) * (1 - sprite.tintAlpha) + tintR);
        g = (int) (float(g) * (1 - sprite.tintAlpha) + tintG);
        b = (int) (float(b) * (1 - sprite.tintAlpha) + tintB);

        color = ((r << 16) | (g << 8) | b);
    }

    // Return the character based on the luminance & color
    return {character, color};
}

void RenderSystem::SetConsoleCharacter(int x, int y, ColoredText character) {
    if (consoleBuffer.is_inside(x, y)) {
        auto &cell = consoleBuffer.get_cell(x, y);
        cell.m_letter = character.character;
        cell.m_format.m_fg_color = {
            (character.color >> 16) & 0xFF,
            (character.color >> 8) & 0xFF,
            character.color & 0xFF
        };
    }
}

void RenderSystem::DrawTriangle(Sprite& sprite, int index) {
    // Create a copy of the points
    Sprite points(3);
    points.alpha = sprite.alpha;
    points.tint = sprite.tint;
    points.tintAlpha = sprite.tintAlpha;

    // Convert the points to screen space, from 0 to dwSize
    const float fontAspectRatio = 0.5f; // The x to y ratio of the font
    auto maxScreenSize = (float)fmax(width, (float)height / fontAspectRatio);

    for (int i = 0; i < 3; i++) {
        points[i].point.x = sprite[i + index].point.x * maxScreenSize + ((float)width - maxScreenSize) * 0.5f;
        points[i].point.y = sprite[i + index].point.y * maxScreenSize * fontAspectRatio + ((float)height - maxScreenSize * fontAspectRatio) * 0.5f;
        points[i].color = sprite[i + index].color;
        points[i].alpha = sprite[i + index].alpha;
    }

    // Check if any of the points are on the screen
    if (points[0].point.x < 0 && points[1].point.x < 0 && points[2].point.x < 0) return;
    if (points[0].point.y < 0 && points[1].point.y < 0 && points[2].point.y < 0) return;
    if (points[0].point.x >= (float)width && points[1].point.x >= (float)width && points[2].point.x >= (float)width) return;
    if (points[0].point.y >= (float)height && points[1].point.y >= (float)height && points[2].point.y >= (float)height) return;

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
    for (int y = (int)fmax(-1, fmin(height, std::ceil(points[0].point.y))); y <= (int)fmax(-1, fmin(height, (points[1].point.y))); y++) {
        auto x1 = (float)fmax(-1, fmin(width, points[0].point.x + slopeAC * ((float)y - points[0].point.y)));
        auto x2 = (float)fmax(-1, fmin(width, points[0].point.x + slopeAB * ((float)y - points[0].point.y)));
        if (x1 > x2) std::swap(x1, x2); // Ensure x1 is always less than x2
        for (int x = (int)std::ceil(x1); x <= (int)(x2); x++) {
            SetConsoleCharacter(x, y, AlphaColorOfPoint(points, x, y));
        }
    }

    // Draw the lower part of the triangle (from B to C)
    for (int y = (int)fmax(-1, fmin(height, std::ceil(points[1].point.y))); y <= (int)fmax(-1, fmin(height, (points[2].point.y))); y++) {
        auto x1 = (float)fmax(-1, fmin(width, points[0].point.x + slopeAC * ((float)y - points[0].point.y)));
        auto x2 = (float)fmax(-1, fmin(width, points[1].point.x + slopeBC * ((float)y - points[1].point.y)));
        if (x1 > x2) std::swap(x1, x2); // Ensure x1 is always less than x2
        for (int x = (int)std::ceil(x1); x <= (int)(x2); x++) {
            SetConsoleCharacter(x, y, AlphaColorOfPoint(points, x, y));
        }
    }
}

void RenderSystem::DrawTextToScreen(Text &text, int x, int y) {
    auto &textStr = text.GetString();

    // Get size of the text
    int stringHeight = (int) textStr.size();
    int stringWidth = 0;
    for (auto &str: textStr)
        stringWidth = (int) fmax(stringWidth, str.size());
    stringWidth += text.leftMargin + text.rightMargin;
    stringHeight += text.topMargin + text.bottomMargin;

    // Draw the black background
    int xLeft, yTop;
    switch (text.hAlign) {
        case HAlign::Left:
            xLeft = x;
            break;
        case HAlign::Center:
            xLeft = x - stringWidth / 2;
            break;
        case HAlign::Right:
            xLeft = x - stringWidth;
            break;
    }
    switch (text.vAlign) {
        case VAlign::Top:
            yTop = y;
            break;
        case VAlign::Center:
            yTop = y - stringHeight / 2;
            break;
        case VAlign::Bottom:
            yTop = y - stringHeight;
            break;
    }

    // Draw Black Rectangle
    for (int i = xLeft; i < xLeft + stringWidth; i++)
        for (int j = yTop; j < yTop + stringHeight; j++)
            SetConsoleCharacter(i, j, {' ', 0});

    // Draw the text
    Color textColor = 0xFFFFFF;
    for (int i = 0; i < (int) textStr.size(); i++) {
        int size = (int)textStr[i].size();
        int xOffset = xLeft + (int)((stringWidth - text.leftMargin - text.rightMargin - size) / 2.0 * ((int)text.hAlign + 1));
        for (int j = 0; j < (int)textStr[i].size(); j++) {
            if (text.HasColor(j, i))
                textColor = text.GetColor(j, i);
            SetConsoleCharacter(xOffset + j + text.leftMargin, yTop + i + text.topMargin, {textStr[i][j], textColor});
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
#elif EMSCRIPTEN
    width = EM_ASM_INT({
        return Module.width;
    });
    height = EM_ASM_INT({
        return Module.height;
    });
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
        consoleBuffer = oof::screen(width, height, ' ');
    }

    // Loop over all the entities
    auto camera = CameraSystem::GetTransform();
    for (auto entity: Engine::GetEntities<Sprite>()) {
        auto entityTransformedSprite = TransformSystem::TransformSprite(
            entity->GetComponent<Sprite>(),
            entity->GetComponent<Transform>()
        );

        // Camera transform
        entityTransformedSprite = TransformSystem::TransformSprite(
            entityTransformedSprite,
            camera
        );

        // Draw the sprite
        for (int i = 0; i < entityTransformedSprite.Size(); i += 3) {
            DrawTriangle(entityTransformedSprite, i);
        }
    }

    // Draw all text based elements
    for (auto entity: Engine::GetEntities<Text>()) {
        auto &text = entity->GetComponent<Text>();
        auto &transform = entity->GetComponent<Transform>();
        DrawTextToScreen(text, (int)(transform.x * (float)width), (int)(transform.y * (float)height));
    }

    // Clear the screen
    if (clearScreen) {
#ifdef _WIN32
        system("cls");
#elif !EMSCRIPTEN
        std::cout << "\033[2J";
#endif
        clearScreen = false;
    }

    // Draw the console buffer
#ifdef _WIN32
    auto const str = consoleBuffer.get_string();
    WriteConsoleA(hStdOut, str.c_str(), (DWORD)str.size(), nullptr, nullptr);
#elif EMSCRIPTEN
    std::string buffer;
    oof::color lastColor = 0;
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            auto &cell = consoleBuffer.get_cell(x, y);
            if (cell.m_letter == ' ')
                buffer += "&nbsp;";
            else {
                if (cell.m_format.m_fg_color != lastColor) {
                    if (!buffer.empty())
                        buffer += "</span>";
                    lastColor = cell.m_format.m_fg_color;
                    buffer += "<span style=\"color:rgb(" + std::to_string(cell.m_format.m_fg_color.red) + "," + std::to_string(cell.m_format.m_fg_color.green) + "," + std::to_string(cell.m_format.m_fg_color.blue) + ")\">";
                }
                buffer += cell.m_letter;
            }
        }
        buffer += "<br>";
    }
    buffer += "</span>";
    EM_ASM({
        Module.canvas.innerHTML = UTF8ToString($0);
    }, buffer.c_str());
#else
    std::cout << consoleBuffer.get_string();
#endif
}
