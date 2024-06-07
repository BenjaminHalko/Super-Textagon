#pragma once

#define PI 3.14159265358979323846f

struct Point {
    float x, y;
};

struct Color {
    unsigned int color;
    float alpha;
};

struct ColoredPoint {
    Point point;
    Color color;
};
