#pragma once

#include <engine/comp/_propertyComponent.h>
#include <engine/entity.h>

class Script : public PropertyComponent {
private:
    void (*_script)(Entity&);
public:
    explicit Script(void (*script)(Entity&));
    void operator()(Entity& self);
};
