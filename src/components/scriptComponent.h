#include "_component.h"

class ScriptComponent : public Component {
private:
    void (*_script)(void);
public:
    ScriptComponent(void (*script)(void)) : _script(script) {}
    void operator()() { _script(); }
};
