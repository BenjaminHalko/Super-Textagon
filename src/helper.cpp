#include "helper.h"
#include <engine/sys/timeSystem.h>
#include <engine/common.h>
#include <cmath>

// Clamp between two values
float Clamp(float value, float min, float max) {
	if (value < min) {
		return min;
	}
	if (value > max) {
		return max;
	}
	return value;
}

// Move a towards b at speed of amount
float Approach(float a, float b, float amount) {
	if (a < b) {
		a += amount * TimeSystem::DeltaTime();
		if (a > b) {
			return b;
		}
	}
	else {
		a -= amount * TimeSystem::DeltaTime();
		if (a < b) {
			return b;
		}
	}
	return a;
}

// Gets the difference between two angles
float AngleDifference(float a, float b) {
	float difference = (float)fmod(b - a + 180, 360) - 180;
	if (difference < -180) {
		difference += 360;
	}
	return difference;
}

float ApproachEase(float value, float target, float maxSpd, float ease) {
	value += Clamp((1 - ease) * (target - value), -maxSpd, maxSpd) * TimeSystem::DeltaTime();
	return value;
}

float ApproachCircleEase(float value, float target, float maxSpd, float ease) {
	value += Clamp((1 - ease) * AngleDifference(value, target), -maxSpd, maxSpd) * TimeSystem::DeltaTime();
	return value;
}

// Returns the direction when given two points
float PointDirection(float x1, float y1, float x2, float y2) {
	return (float)(std::atan2(y2 - y1, x2 - x1) * 180 / PI);
}

// Returns the distance when given two points
float PointDistance(float x1, float y1, float x2, float y2) {
	return (float)sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Given a length and direction, return x component
float LengthDir_x(float len, float dir) {
	return (float)cos(dir * PI / 180) * len;
}

// Given a length and direction, return x component
float LengthDir_y(float len, float dir) {
	return (float)sin(dir * PI / 180) * len;
}

// Returns a random number between min and max
float RandomRange(float min, float max) {
	return min + (max - min) * (float)rand() / RAND_MAX;
}

// Merges 2 colors
Color MergeColors(Color col1, Color col2, float percent) {
    int r = (int)((float)(col1 >> 16 & 0xFF) * (1 - percent) + (float)(col2 >> 16 & 0xFF) * percent);
    int g = (int)((float)(col1 >> 8 & 0xFF) * (1 - percent) + (float)(col2 >> 8 & 0xFF) * percent);
    int b = (int)((float)(col1 & 0xFF) * (1 - percent) + (float)(col2 & 0xFF) * percent);

    return (r << 16) | (g << 8) | b;
}

// Generate a color
Color MakeColor(float hue, float sat, float val) {
    float c = val * sat;
    auto x = (float)(c * (1 - abs(fmod(hue / 60, 2) - 1)));
    float m = val - c;

    float r, g, b;
    if (hue < 60) {
        r = c;
        g = x;
        b = 0;
    } else if (hue < 120) {
        r = x;
        g = c;
        b = 0;
    } else if (hue < 180) {
        r = 0;
        g = c;
        b = x;
    } else if (hue < 240) {
        r = 0;
        g = x;
        b = c;
    } else if (hue < 300) {
        r = x;
        g = 0;
        b = c;
    } else {
        r = c;
        g = 0;
        b = x;
    }

    return ((int)((r + m) * 255) << 16) | ((int)((g + m) * 255) << 8) | (int)((b + m) * 255);
}

// Waves between min and max
float Wave(float min, float max, float duration, float offset) {
    return (min + max) / 2 + (max - min) / 2 * sin((TimeSystem::TimeRunning() + offset) * 2 * PI / duration);
}
