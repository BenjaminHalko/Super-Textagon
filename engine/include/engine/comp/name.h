#pragma once

#include <engine/comp/_component.h>
#include <string>

class Name : public Component {
    std::string _name;
public:
    Name(std::string name);
    std::string Get() const;
};
