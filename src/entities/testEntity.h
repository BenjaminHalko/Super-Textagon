#pragma once

#include <engine/entity.h>

class TestEntity : public Entity {
    int _offset;

public:
    TestEntity(int offset);

    void Update() override;
};
