#pragma once

float Clamp(float value, float min, float max);
float Approach(float a, float b, float amount);
float AngleDifference(float a, float b);
float ApproachEase(float value, float target, float maxSpd, float ease);
float ApproachCircleEase(float value, float target, float maxSpd, float ease);
