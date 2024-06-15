#pragma once

#include <engine/comp/_propertyComponent.h>
#include <string>

class Name : public PropertyComponent {
    std::string _name;
public:
    explicit Name(std::string name);
    std::string Get() const;
};


