#include <engine/comp/tag.h>

Tag::Tag(std::string tag) : _tag(std::move(tag)) {}

std::string Tag::Get() const {
    return _tag;
}
