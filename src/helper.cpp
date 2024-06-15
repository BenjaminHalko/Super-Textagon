#include "helper.h"
#include <engine/sys/timeSystem.h>
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
