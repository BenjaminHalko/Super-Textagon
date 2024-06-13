#pragma once

#include <engine/sys/_system.h>
#include <engine/comp/audioComponent.h>
#include <soloud_wav.h>
#include <string>
#include <vector>



class AudioSystem : public System {
    friend class Engine;
    static SoLoud::Soloud _soLoud;
    static std::vector<std::pair<std::unique_ptr<SoLoud::Wav>, unsigned int>> _audioClips;

    static void Init();
    static void Update();
    static void Clean();

public:
    static AudioComponent PlayAudio(std::string audioPath, bool loop, float volume);
    static void StopAudio(AudioComponent& audio);

    static float GetAudioPosition(AudioComponent& audio);
    static void SetAudioPosition(AudioComponent& audio, float position);

    static float GetAudioVolume(AudioComponent& audio);
    static void SetAudioVolume(AudioComponent& audio, float volume);

    static void PauseAudio(AudioComponent& audio);
    static void ResumeAudio(AudioComponent& audio);

    static void StopAllAudio();
    static void SetGlobalVolume(float volume);
};
