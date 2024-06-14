#include <engine/entity.h>

bool Entity::operator<(const Entity &other) const {
    return _depth < other._depth;
}
