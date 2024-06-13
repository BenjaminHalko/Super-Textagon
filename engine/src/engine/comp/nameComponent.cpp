#include <engine/comp/nameComponent.h>

NameComponent::NameComponent(std::string name) : _name(name) {}
std::string NameComponent::Get() const { return _name; }
