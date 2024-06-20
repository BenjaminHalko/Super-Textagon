#include <engine/comp/text.h>
#include <engine/common.h>

Text::Text(
    std::initializer_list<std::string> text,
    HAlign hAlign,
    VAlign vAlign,
    int leftMargin,
    int rightMargin,
    int topMargin,
    int bottomMargin
) : hAlign(hAlign), vAlign(vAlign), leftMargin(leftMargin), rightMargin(rightMargin), topMargin(topMargin), bottomMargin(bottomMargin) {
    _text.resize(text.size());
    std::copy(text.begin(), text.end(), _text.begin());
}

Text::Text(
    std::vector<std::string> text,
    HAlign hAlign, VAlign vAlign,
    int leftMargin,
    int rightMargin,
    int topMargin,
    int bottomMargin
) : _text(std::move(text)), hAlign(hAlign), vAlign(vAlign), leftMargin(leftMargin), rightMargin(rightMargin), topMargin(topMargin), bottomMargin(bottomMargin) {}

Text::Text(int size)
    : hAlign(HAlign::Left), vAlign(VAlign::Top), leftMargin(1), rightMargin(1), topMargin(1), bottomMargin(1) {
    _text.resize(size);
}

std::vector<std::string>& Text::GetString() {
    return _text;
}

void Text::SetColor(int x, int y, Color color) {
    auto key = (size_t) x << 8 | (unsigned int) y;
    _color[key] = color;
}

Color Text::GetColor(int x, int y) {
    auto key = (size_t) x << 8 | (unsigned int) y;
    return _color[key];
}

bool Text::HasColor(int x, int y) {
    auto key = (size_t) x << 8 | (unsigned int) y;
    return _color.find(key) != _color.end();
}
