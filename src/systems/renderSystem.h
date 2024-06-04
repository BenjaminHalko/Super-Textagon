#pragma once

#include "_system.h"
#include <iostream>
#include <string>
#include <curses.h>

class RenderSystem : public System {
    int num = 0;

    /**
     * @brief Prints a string to the console, really fast
     * @param str
     */
    static void FastPrint(const std::string &str) {
        mvprintw(0, 0, str.c_str());
    }
public:
    RenderSystem() {
        initscr(); // Initialize the screen
        cbreak(); // Disable line buffering
        noecho(); // Don't echo the input
        nodelay(stdscr, TRUE); // Don't wait for input
        keypad(stdscr, TRUE); // Enable the keypad
        timeout(0); // Non-blocking getch
    }

    ~RenderSystem() override {
        endwin(); // End the window
    }

    void UpdateEntity(Entity &entity) override {
        // Render the entity
    }

    void PreUpdate() override {
        // Clear the screen
        refresh();
    }

    void PostUpdate() override {
        // Display the frame
        if (Input::GetKeyDown(Key::LEFT)) {
            std::string str = "Frame: " + std::to_string(num++);
            FastPrint(str);
        }
    }
};
