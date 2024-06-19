#pragma once

#include <engine/comp/_component.h>
#include <engine/common.h>
#include <vector>
#include <string>
#include <map>

/**
 * @brief Enum class for horizontal alignment.
 */
enum class HAlign {
    Left = -1,
    Center = 0,
    Right = 1
};

/**
 * @brief Enum class for vertical alignment.
 */
enum class VAlign {
    Top = -1,
    Center = 0,
    Bottom = 1
};

/**
 * @brief A component that represents text.
 * @details This class stores a collection of strings that can be drawn on the screen.
 */
class Text : public Component {
    std::vector<std::string> _text;
    std::map<size_t, Color> _color{};
public:
    HAlign hAlign;
    VAlign vAlign;
    int leftMargin;
    int topMargin;
    int bottomMargin;
    int rightMargin;

    /**
     * @brief Constructs a Text from an initializer list of strings.
     *
     * @param text Initializer list of strings to initialize the text.
     * @param hAlign The horizontal alignment of the text.
     * @param vAlign The vertical alignment of the text.
     * @param leftMargin The left margin of the text.
     * @param rightMargin The right margin of the text.
     * @param topMargin The top margin of the text.
     * @param bottomMargin The bottom margin of the text.
     */
    Text(
        std::initializer_list<std::string> text,
        HAlign hAlign = HAlign::Left,
        VAlign vAlign = VAlign::Top,
        int leftMargin = 0,
        int rightMargin = 0,
        int topMargin = 0,
        int bottomMargin = 0
    );

    /**
     * @brief Constructs a Text from a vector of strings.
     *
     * @param text Vector of strings to initialize the text.
     * @param hAlign The horizontal alignment of the text.
     * @param vAlign The vertical alignment of the text.
     * @param leftMargin The left margin of the text.
     * @param rightMargin The right margin of the text.
     * @param topMargin The top margin of the text.
     * @param bottomMargin The bottom margin of the text.
     */
    explicit Text(
        std::vector<std::string> text,
        HAlign hAlign = HAlign::Left,
        VAlign vAlign = VAlign::Top,
        int leftMargin = 0,
        int rightMargin = 0,
        int topMargin = 0,
        int bottomMargin = 0
    );

    /**
     * @brief Constructs a Text with a specified size.
     *
     * @param size The number of strings to reserve for the text.
     */
    explicit Text(int size);

    /**
     * @brief Retrieves the text.
     *
     * @return The text.
     */
    [[nodiscard]] std::vector<std::string>& GetString();

    /**
     * @brief Sets the color of a character.
     * @details This function sets the color of a character at a specified position.
     * @param x The x-coordinate of the character.
     * @param y The y-coordinate of the character.
     * @param color The color to set.
     */
    void SetColor(int x, int y, Color color);

    /**
     * @brief Retrieves the color of a character.
     * @details This function retrieves the color of a character at a specified position.
     * @param x The x-coordinate of the character.
     * @param y The y-coordinate of the character.
     * @return The color of the character.
     */
    [[nodiscard]] Color GetColor(int x, int y);

    /**
     * @brief Retrieves if the color of a character exists.
     * @details This function retrieves if the color of a character at a specified position exists.
     * @param x The x-coordinate of the character.
     * @param y The y-coordinate of the character.
     * @return True if the color of a character exists, false otherwise.
     */
    [[nodiscard]] bool HasColor(int x, int y);
};
