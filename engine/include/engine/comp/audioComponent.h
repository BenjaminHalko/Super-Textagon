#pragma once

#include <engine/comp/_component.h>
#include <string>

class AudioComponent : public Component {
private:
    std::string _audioPath;
    bool _isPlaying = false;
    bool _loop;
public:
    explicit AudioComponent(std::string audioPath);

    std::string GetAudioPath();
};
