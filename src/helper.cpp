#include "helper.h"
#include "global.h"
#include <engine/sys/timeSystem.h>
#include <engine/sys/cameraSystem.h>
#include <engine/common.h>
#include <cmath>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>

// Wrap between two values
float Wrap(float value, float min, float max) {
    if (fmod(value, 1) == 0) {
	    while (value > max || value < min) {
	        if (value > max)
	            value += min - max - 1;
	        else if (value < min)
	            value += max - min + 1;
	    }
	    return value;
	} else {
	    float valueOld = value + 1;
	    while (value != valueOld) {
	        valueOld = value;
	        if (value < min)
	            value = max - (min - value);
	        else if (value > max)
	            value = min + (value - max);
	    }
	    return value;
	}

}

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

// Transform a sprite using global zoom
void ZoomSprite(Sprite& sprite, Sprite& originalSprite, float zoom) {
    if (zoom == -1)
        zoom = Global::zoom + CameraSystem::zoom - 1.0f;

    for (int i = 0; i < sprite.Size(); i++) {
        float dir = PointDirection(0, 0, originalSprite[i].point.x, originalSprite[i].point.y);

        if (originalSprite[i].point.x != 0)
            sprite[i].point.x = originalSprite[i].point.x + LengthDir_x(zoom/abs(originalSprite[i].point.x*2.0f+1.0f)*0.02f, dir);

        if (originalSprite[i].point.y != 0)
            sprite[i].point.y = originalSprite[i].point.y + LengthDir_y(zoom/abs(originalSprite[i].point.y*2.0f+1.0f)*0.02f, dir);
    }
}

// Gets the amount of time the game has been running for
float RoundRunning() {
    if (Global::gameOver)
        return Global::finalScore;
    return TimeSystem::TimeRunning() - Global::roundStart;
}

// Formats time
std::string FormatTime(float time) {
    int minutes = (int)time / 60;
    int seconds = (int)time % 60;
    std::string secondsStr = std::to_string(seconds);
    if (minutes > 0 && seconds < 10)
        secondsStr = "0" + secondsStr;
    int milliseconds = (int)(time * 100) % 100;
    std::string millisecondsStr = std::to_string(milliseconds);
    if (milliseconds < 10)
        millisecondsStr = "0" + millisecondsStr;
    if (minutes == 0)
        return secondsStr + "." + millisecondsStr;
    return std::to_string(minutes) + ":" + secondsStr + "." + millisecondsStr;
}

bool fileExists(const std::string& fileName) {
	// Returns false if file doesn't exist/can't be opened
	std::ifstream file(fileName);
	return file.good();
}

void Save(float score) {
    std::string fileName = "save";
    char* localAppdata = std::getenv("LOCALAPPDATA");
	if (localAppdata != nullptr) {
		std::string folder = (std::string)localAppdata + "\\Super_Textagon";
		struct stat info{};
		stat(folder.c_str(), &info);

        if (!(info.st_mode & S_IFDIR)) {
            std::string command = "mkdir " + folder;
            int createdFolder = system(command.c_str());
            if (createdFolder == 0)
                fileName = folder + "\\" + fileName;
        }
        else {
            fileName = folder + "\\" + fileName;
        }
	}
	fileName = fileName + ".sav";
	std::ofstream outFile(fileName, std::ios::trunc);
	outFile << score;
	outFile.close();
}

float Load() {
    std::string fileName = "save";
    char* localAppdata = std::getenv("LOCALAPPDATA");
	if (localAppdata != nullptr)
		fileName = (std::string)localAppdata + "\\Super_Textagon\\" + fileName;
	fileName = fileName + ".sav";
	float score;
	std::ifstream inFile;
	if (fileExists(fileName)) {
		inFile.open(fileName);
		if (inFile >> score) {
			return score;
		}
	}
	return 0;
}

int GetShapePhase() {
    float time = RoundRunning();
    if (time < 10.0f)
        return 0;
    if (time < 20.0f)
        return 1;
    if (time < 30.0f)
        return 2;
    if (time < 45.0f)
        return 3;
    if (time < 60.0f)
        return 4;
    return 5;
}
