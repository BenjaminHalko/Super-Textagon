#include <engine/comp/script.h>

Script::Script(void (*script)(Entity&)) : _script(script) {}

void Script::operator()(Entity& self) {
    _script(self);
}
