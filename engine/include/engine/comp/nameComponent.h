#pragma once

#include <engine/comp/_uniqueComponent.h>
#include <string>

class NameComponent : public UniqueComponent {
    std::string _name;
public:
    NameComponent(std::string name);
    std::string Get() const;
};
