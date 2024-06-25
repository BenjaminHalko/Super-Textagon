#include <engine/sys/audioSystem.h>
#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#ifndef EMSCRIPTEN
// Declare the static variables
SoLoud::Soloud AudioSystem::_soLoud;
std::vector<std::pair<std::unique_ptr<SoLoud::WavStream>, unsigned int>> AudioSystem::_audioClips;

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
    std::pair<std::unique_ptr<SoLoud::WavStream>, unsigned int> audioClip;
    audioClip.first = std::make_unique<SoLoud::WavStream>();
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
#else
float AudioSystem::_globalVolume = 1.0f;

void AudioSystem::Init() {
    // Preload all audio in the audio folder
    // There is probably a better way to do this
    EM_ASM({
        FS.readdir('/audio').forEach(function(file) {
            if (FS.analyzePath('/audio/' + file).isFile) {
                var audio = new Audio('/audio/' + file);
                audio.volume = 0;
                audio.play();
                audio.pause();
            }
        });
    });
}

void AudioSystem::Update() {}

void AudioSystem::Clean() {}

AudioComponent AudioSystem::PlayAudio(std::string audioPath, bool loop, float volume) {
    int handle = EM_ASM_INT({
        var audio = new Audio(UTF8ToString($0));
        audio.loop = $1;
        audio.volume = $2 * $3;
        audio.play();
        var handle = Module.audioHandles.length;
        Module.audioHandles.push([audio, $2]);
        return handle;
    }, audioPath.c_str(), loop, volume, _globalVolume);

    return AudioComponent(handle);
}

void AudioSystem::StopAudio(AudioComponent& audio) {
    EM_ASM_({
        var audio = Module.audioHandles[$0][0];
        audio.pause();
        audio.currentTime = 0;
    }, audio());
}

float AudioSystem::GetAudioPosition(AudioComponent& audio) {
    return (float)EM_ASM_DOUBLE({
        var audio = Module.audioHandles[$0][0];
        return audio.currentTime;
    }, audio());
}

void AudioSystem::SetAudioPosition(AudioComponent& audio, float position) {
    EM_ASM_({
        var audio = Module.audioHandles[$0][0];
        audio.currentTime = $1;
    }, audio(), position);
}

float AudioSystem::GetAudioVolume(AudioComponent& audio) {
    return (float)EM_ASM_DOUBLE({
        return Module.audioHandles[$0][1];
    }, audio());
}

void AudioSystem::SetAudioVolume(AudioComponent& audio, float volume) {
    EM_ASM_({
        var audio = Module.audioHandles[$0][0];
        Module.audioHandles[$0][1] = $1;
        audio.volume = $1 * $2;
    }, audio(), volume, _globalVolume);
}

void AudioSystem::PauseAudio(AudioComponent& audio) {
    EM_ASM_({
        var audio = Module.audioHandles[$0][0];
        audio.pause();
    }, audio());
}

void AudioSystem::ResumeAudio(AudioComponent& audio) {
    EM_ASM_({
        var audio = Module.audioHandles[$0][0];
        audio.play();
    }, audio());
}

void AudioSystem::StopAllAudio() {
    EM_ASM({
        for (var i = 0; i < Module.audioHandles.length; i++) {
            Module.audioHandles[i][0].pause();
            Module.audioHandles[i][0].currentTime = 0;
        }
    });
}

void AudioSystem::SetGlobalVolume(float volume) {
    if (_globalVolume != volume) {
        _globalVolume = volume;
        EM_ASM_({
            for (var i = 0; i < Module.audioHandles.length; i++) {
                Module.audioHandles[i][0].volume = Module.audioHandles[i][1] * $0;
            }
        }, volume);
    }
}
#endif
