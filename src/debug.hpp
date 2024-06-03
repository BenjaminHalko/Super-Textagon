#pragma once

#include <iostream>

/**
 * @brief Print all arguments to the console
 * @tparam Args
 */
template <typename... Args>
void Print(Args&&... args) {
    for(auto&& arg : {args...}) {
        std::cout << arg << ", ";
    }
    std::cout << std::endl;
}
