#pragma once

#include "_component.hpp"
#include <vector>
#include <string>

class SpriteComponent : public Component {
    std::vector<std::string> sprite;
public:
    explicit SpriteComponent(std::vector<std::string> sprite) : sprite(std::move(sprite)), Component() {}
};
