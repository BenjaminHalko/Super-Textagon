#pragma once

#include <engine/comp/_component.h>
#include <engine/entity.h>

class Script : public Component {
private:
    void (*_script)(Entity&);
public:
    explicit Script(void (*script)(Entity&));
    void operator()(Entity& self);
};
