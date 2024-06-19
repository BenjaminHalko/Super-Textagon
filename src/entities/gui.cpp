#include "gui.h"
#include "../helper.h"
#include <engine/engine.h>
#include <engine/comp/text.h>
#include <engine/comp/depth.h>
#include <engine/comp/transform.h>
#include <engine/comp/script.h>
#include <engine/comp/tag.h>

void UpdateProgress(Entity& self) {
    auto& text = self.GetComponent<Text>();
    static const int progressSize = (int)text.GetString()[1].size();
    static const std::vector<std::string> shapes = {
        "POINT", "LINE", "TRIANGLE", "SQUARE", "PENTAGON", "HEXAGON"
    };

    float progress = 1;
    if (RoundRunning() < 30) {
        progress = (float)fmod(RoundRunning(), 10) / 10.0f;
        text.GetString()[0] = shapes[(int)RoundRunning() / 10];
    } else if (RoundRunning() < 60) {
        progress = (float)fmod(RoundRunning(), 15) / 15.0f;
        text.GetString()[0] = shapes[(int)RoundRunning() / 15 + 1];
    } else {
        text.GetString()[0] = shapes[5];
    }
    for(int i = 0; i < progressSize; i++) {
        float alpha = Clamp((float)progressSize * progress - (float)i, 0, 1);
        text.SetColor(i, 1, MergeColors(0x222222, 0xFFFFFF, alpha));
    }
}

void UpdateTopRightScore(Entity& self) {
    auto& text = self.GetComponent<Text>();
    text.GetString()[1] = FormatTime(RoundRunning());
}

void CreateGUI() {
    Engine::AddEntity(
        Tag("GUI"),
        Depth(-500),
        Text({"Pentagon", "----------"}, HAlign::Left, VAlign::Top, 1, 1, 0, 0),
        Transform(0, 0),
        Script(UpdateProgress)
    );

    Engine::AddEntity(
        Tag("GUI"),
        Depth(-500),
        Text({"TIME", "0"}, HAlign::Right, VAlign::Top, 1, 1, 0, 0),
        Transform(1, 0),
        Script(UpdateTopRightScore)
    );
}

void CreateIntroGUI() {
    Engine::AddEntity(
        Tag("GUI"),
        Depth(-500),
        Text({"Super", "Textagon"}, HAlign::Center, VAlign::Center, 1, 1, 0, 0),
        Transform(0.5f, 0.5f)
    );
}
