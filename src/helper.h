#pragma once
#include <engine/comp/sprite.h>
#include <string>

float Wrap(float value, float min, float max);
float Clamp(float value, float min, float max);
float Approach(float a, float b, float amount);
float AngleDifference(float a, float b);
float ApproachEase(float value, float target, float maxSpd, float ease);
float ApproachCircleEase(float value, float target, float maxSpd, float ease);
float PointDirection(float x1, float y1, float x2, float y2);
float PointDistance(float x1, float y1, float x2, float y2);
float LengthDir_x(float len, float dir);
float LengthDir_y(float len, float dir);
float RandomRange(float min, float max);
Color MergeColors(Color col1, Color col2, float percent);
Color MakeColor(float hue, float sat, float val);
float Wave(float min, float max, float duration, float offset);
void ZoomSprite(Sprite& sprite, Sprite& originalSprite, float zoom = -1);
float RoundRunning();
std::string FormatTime(float time);
