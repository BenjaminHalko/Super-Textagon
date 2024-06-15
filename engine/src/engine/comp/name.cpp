#include <engine/comp/name.h>

Name::Name(std::string name) : _name(std::move(name)) {}

std::string Name::Get() const {
    return _name;
}
