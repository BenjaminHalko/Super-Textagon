#include <engine/entity.h>

void Entity::Delete() {
    _delete = true;
}

bool Entity::IsDeleted() const {
    return _delete;
}
