#pragma once

#include <engine/comp/_component.h>

class Depth : public Component {
    int _depth;
public:
    explicit Depth(int depth);
    [[nodiscard]] int Get() const;
};
