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
        "POINT", "LINE", "TRIANGLE", "SQUARE", "PENTAGON", "TEXTAGON"
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

void UpdateGameOverGUI(Entity& self) {
    auto& text = self.GetComponent<Text>();
    auto& transform = self.GetComponent<Transform>();
    transform.x = ApproachEase(transform.x, 0.5f + 0.5f * float(text.hAlign), 0.1f, 0.8f);
}

void CreateGUI() {
    auto &progress = Engine::AddEntity(
        Tag("GUI"),
        Depth(-500),
        Text({"POINT", "----------"}, HAlign::Left, VAlign::Top, 1, 1, 0, 0),
        Transform(0, 0),
        Script(UpdateProgress)
    );
    UpdateProgress(progress);

    auto &score = Engine::AddEntity(
        Tag("GUI"),
        Depth(-500),
        Text({"TIME", "0"}, HAlign::Right, VAlign::Top, 1, 1, 0, 0),
        Transform(1, 0),
        Script(UpdateTopRightScore)
    );
    UpdateTopRightScore(score);
}

void CreateIntroGUI() {
    Engine::AddEntity(
        Tag("GUI"),
        Depth(-500),
        Text({
            "         ______  _____  _______        ",
            "        / __/ / / / _ \\/ __/ _ \\       ",
            "        _\\ \\/ /_/ / ___/ _// , _/       ",
            "       /___/\\____/_/  /___/_/|_|        ",
            " ___________  ___________  _________  _  __",
            "/_  __/ __/ |/_/_  __/ _ |/ ___/ __ \\/ |/ /",
            " / / / _/_>  <  / / / __ / (_ / /_/ /    / ",
            "/_/ /___/_/|_| /_/ /_/ |_\\___/\\____/_/|_/  "
        }, HAlign::Center, VAlign::Center, 1, 1, 0, 1),
        Transform(0.5f, 0.5f)
    );
}

void CreateGameOverGUI(float highScore) {
    std::vector<std::string> text;
    if(highScore < 10) {
        text = {
            " _    _____   _____ _      _ ",
            "| |  | __\\ \\ / / __| |    / |",
            "| |__| _| \\ V /| _|| |__  | |",
            "|____|___| \\_/ |___|____| |_|",
            "",
            "                        POINT"
        };
    } else if(highScore < 20) {
        text = {
            " _    _____   _____ _      ___ ",
            "| |  | __\\ \\ / / __| |    |_  )",
            "| |__| _| \\ V /| _|| |__   / / ",
            "|____|___| \\_/ |___|____| /___|",
            "",
            "                        LINE"
        };
    } else if(highScore < 30) {
        text = {
            " _    _____   _____ _      ____",
            "| |  | __\\ \\ / / __| |    |__ /",
            "| |__| _| \\ V /| _|| |__   |_ \\",
            "|____|___| \\_/ |___|____| |___/",
            "",
            "                        TRIANGLE"
        };
    } else if(highScore < 45) {
        text = {
            " _    _____   _____ _      _ _  ",
            "| |  | __\\ \\ / / __| |    | | | ",
            "| |__| _| \\ V /| _|| |__  |_  _|",
            "|____|___| \\_/ |___|____|   |_| ",
            "",
            "                        SQUARE"
        };
    } else if(highScore < 60) {
        text = {
            " _    _____   _____ _      ___ ",
            "| |  | __\\ \\ / / __| |    | __|",
            "| |__| _| \\ V /| _|| |__  |__ \\",
            "|____|___| \\_/ |___|____| |___/",
            "",
            "                        PENTAGON"
        };
    } else {
        text = {
            " _    _____   _____ _       __ ",
            "| |  | __\\ \\ / / __| |     / / ",
            "| |__| _| \\ V /| _|| |__  / _ \\",
            "|____|___| \\_/ |___|____| \\___/",
            "",
            "                          TEXTAGON"
        };
    }

    Engine::AddEntity(
        Tag("GUI"),
        Depth(-500),
        Text(text, HAlign::Left, VAlign::Center, 20, 1, 0, 1),
        Transform(-0.5f, 0.5f),
        Script(UpdateGameOverGUI)
    );

    std::string timeText = "TIME: "+FormatTime(RoundRunning());
    std::string extraSpacing(timeText.size(), ' ');
    Engine::AddEntity(
        Tag("GUI"),
        Depth(-500),
        Text({
            " _      _   ___ _____    "+extraSpacing,
            "| |    /_\\ / __|_   _|   "+extraSpacing,
            "| |__ / _ \\\\__ \\ | |     "+timeText,
            "|____/_/ \\_\\___/ |_|     "+extraSpacing
        }, HAlign::Right, VAlign::Center, 1, 25, 0, 1),
        Transform(1.5f, 0.38f),
        Script(UpdateGameOverGUI)
    );

    if (highScore > RoundRunning()) {
        timeText = "TIME: " + FormatTime(highScore);
        extraSpacing = std::string(timeText.size(), ' ');
        Engine::AddEntity(
            Tag("GUI"),
            Depth(-500),
            Text({
                 " ___ ___ ___ _____    " + extraSpacing,
                 "| _ ) __/ __|_   _|   " + extraSpacing,
                 "| _ \\ _|\\__ \\ | |     " + timeText,
                 "|___/___|___/ |_|     " + extraSpacing
             }, HAlign::Right, VAlign::Center, 1, 20, 0, 1),
            Transform(1.5f, 0.62f),
            Script(UpdateGameOverGUI)
        );
    } else {
        Engine::AddEntity(
            Tag("GUI"),
            Depth(-500),
            Text({
                "  _  _ _____      __  ___ ___ ___ ___  ___ ___  ",
                " | \\| | __\\ \\    / / | _ \\ __/ __/ _ \\| _ \\   \\ ",
                " | .` | _| \\ \\/\\/ /  |   / _| (_| (_) |   / |) |",
                " |_|\\_|___| \\_/\\_/   |_|_\\___\\___\\___/|_|_\\___/ ",
            }, HAlign::Right, VAlign::Center, 1, 4, 0, 1),
            Transform(1.5f, 0.62f),
            Script(UpdateGameOverGUI)
        );
    }
}
