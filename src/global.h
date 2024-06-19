#pragma once

#define BaseWallSpd 0.005f
#define BasePlayerSpd 9

#define CHEATS true

class Global {
public:
    static bool beatPulse;
    static float finalScore;
    static float musicTime;
    static float hue;
    static float zoom;
    static float roundStart;
    static float gameSpeed;
    static bool gameOver;
    static bool showGameOverUI;
};
