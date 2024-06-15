#include <engine/comp/depth.h>

Depth::Depth(int depth) : _depth(depth) {}

int Depth::Get() const {
    return _depth;
}
