#include <engine/sys/renderSystem.h>
#include <engine/engine.h>
#include <engine/sys/transformSystem.h>
#include <engine/sys/cameraSystem.h>
#include <limits>
#include <cmath>
#ifndef _WIN32
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

void RenderSystem::Init() {
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

std::pair<char, Color> RenderSystem::AlphaColorOfPoint(Sprite &sprite, int x, int y) {
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
    alpha *= sprite.alpha;

    // Clamp the alpha
    alpha = (float)fmax(0, fmin(1, alpha));

    // Calculate the character
    char character = alphaChars.at((int)((float)(alphaCharsCount-1) * alpha));

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

    // Merge the colour
    if (sprite.tintAlpha != 0) {
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

void RenderSystem::SetConsoleCharacter(int x, int y, std::pair<char, Color> character) {
    if (consoleBuffer.is_inside(x, y)) {
        auto &cell = consoleBuffer.get_cell(x, y);
        cell.m_letter = character.first;
        cell.m_format.m_fg_color = {
            (character.second >> 16) & 0xFF,
            (character.second >> 8) & 0xFF,
            character.second & 0xFF
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
        consoleBuffer = oof::screen(width, height, ' ');
    } else {
        // Clear the console buffer
        consoleBuffer.clear();
    }

    // Loop over all the entities
    auto camera = CameraSystem::GetTransform();
    for (auto entity: Engine::GetEntities<Sprite, Transform>()) {
        auto sprite = entity->GetComponent<Sprite>();

        auto entityTransformedSprite = TransformSystem::TransformSprite(
                entity->GetComponent<Sprite>(),
                entity->GetComponent<Transform>()
        );

        // Camera transform
        entityTransformedSprite = TransformSystem::TransformSprite(
            entityTransformedSprite,
            camera
        );

        for (int i = 0; i < entityTransformedSprite.Size(); i += 3) {
            DrawTriangle(entityTransformedSprite, i);
        }
    }

    // Clear the screen
    if (clearScreen) {
#ifdef _WIN32
        system("cls");
#else
        std::cout << "\033[2J";
#endif
        clearScreen = false;
    }

    // Draw the console buffer
#ifdef _WIN32
    auto const str = consoleBuffer.get_string();
    WriteConsoleA(hStdOut, str.c_str(), (DWORD)str.size(), nullptr, nullptr);
#else
    std::cout << consoleBuffer.get_string();
#endif
}
