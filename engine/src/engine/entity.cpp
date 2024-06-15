#include <engine/entity.h>

std::string Entity::GetName() const {
    return _name;
}

bool Entity::operator<(const Entity &other) const {
    return _depth < other._depth;
}

void Entity::Delete() {
    _delete = true;
}

bool Entity::IsDeleted() const {
    return _delete;
}
