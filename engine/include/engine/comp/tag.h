#pragma once

#include <engine/comp/_component.h>
#include <string>

class Tag : public Component {
    std::string _tag;
public:
    explicit Tag(std::string tag);
    [[nodiscard]] std::string Get() const;
};


