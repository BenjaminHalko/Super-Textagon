#include <curses.h>
#include <string>

/**
 * @brief Prints a string to the console
 * @tparam Text
 */
template <typename Text>
void PrintValue(Text text) {
    static int printCounter = 0;
    auto formattedText = "[" + std::to_string(printCounter++) + "] " + std::to_string(text);
    mvprintw(0, 0, formattedText.c_str());
}

void Print(std::string text) {
    static int printCounter = 0;
    std::string formattedText = "[" + std::to_string(printCounter++) + "] " + text;
    mvprintw(0, 0, "%s", formattedText.c_str());
}
