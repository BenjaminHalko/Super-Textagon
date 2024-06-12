#include <engine/sys/audioSystem.h>

// Declare the static variables
SoLoud::Soloud AudioSystem::_soLoud;
std::vector<std::pair<std::unique_ptr<SoLoud::Wav>, unsigned int>> AudioSystem::_audioClips;

void AudioSystem::Init() {
    _soLoud.init();
}

void AudioSystem::Update() {
    for(int i = 0; i < _audioClips.size(); i++) {
        if (!_soLoud.isValidVoiceHandle(_audioClips[i].second))
            _audioClips.erase(_audioClips.begin() + i);
    }
}

void AudioSystem::Clean() {
    _soLoud.deinit();
}

AudioComponent AudioSystem::PlayAudio(std::string audioPath, bool loop, float volume) {
    std::pair<std::unique_ptr<SoLoud::Wav>, unsigned int> audioClip;
    audioClip.first = std::make_unique<SoLoud::Wav>();
    audioClip.first->load(audioPath.c_str());
    audioClip.first->setLooping(loop);
    audioClip.first->setVolume(volume);
    audioClip.second = _soLoud.play(*audioClip.first);

    _audioClips.push_back(std::move(audioClip));

    return AudioComponent(audioClip.second);
}

void AudioSystem::StopAudio(AudioComponent& audio) {
    _soLoud.stop(audio());
}

float AudioSystem::GetAudioPosition(AudioComponent& audio) {
    return (float)_soLoud.getStreamTime(audio());
}

void AudioSystem::SetAudioPosition(AudioComponent& audio, float position) {
    _soLoud.seek(audio(), position);
}

float AudioSystem::GetAudioVolume(AudioComponent& audio) {
    return _soLoud.getVolume(audio());
}

void AudioSystem::SetAudioVolume(AudioComponent& audio, float volume) {
    _soLoud.setVolume(audio(), volume);
}

void AudioSystem::PauseAudio(AudioComponent& audio) {
    _soLoud.setPause(audio(), true);
}

void AudioSystem::ResumeAudio(AudioComponent& audio) {
    _soLoud.setPause(audio(), false);
}

void AudioSystem::StopAllAudio() {
    _soLoud.stopAll();
}

void AudioSystem::SetGlobalVolume(float volume) {
    _soLoud.setGlobalVolume(volume);
}
