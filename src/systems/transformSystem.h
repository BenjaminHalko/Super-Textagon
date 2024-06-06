#include "_system.h"

class TransformSystem : public System {
public:
    void UpdateEntity(Entity &entity) override;
};
