#pragma once

#include <engine/comp/_component.h>

class Script : public Component {
private:
    void (*_script)();
public:
    explicit Script(void (*script)()) : _script(script) {}
    void operator()();
};
