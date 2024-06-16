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
