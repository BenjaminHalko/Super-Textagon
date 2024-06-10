#pragma once

#include <engine/comp/_component.h>

class ScriptComponent : public Component {
private:
    void (*_script)();
public:
    explicit ScriptComponent(void (*script)()) : _script(script) {}
    void operator()();
};
