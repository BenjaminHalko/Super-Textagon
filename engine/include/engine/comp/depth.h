#pragma once

#include <engine/comp/_propertyComponent.h>

class Depth : public PropertyComponent {
    int _depth;
public:
    explicit Depth(int depth);
    int Get() const;
};
