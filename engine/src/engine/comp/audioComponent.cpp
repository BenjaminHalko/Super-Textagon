#include <engine/comp/audioComponent.h>

AudioComponent::AudioComponent(std::string audioPath) : _audioPath(std::move(audioPath)) {}

std::string AudioComponent::GetAudioPath() {
    return _audioPath;
}
