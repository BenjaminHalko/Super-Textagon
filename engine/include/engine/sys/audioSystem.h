#pragma once

#include <engine/sys/_system.h>
#include <engine/comp/audio.h>
#include <soloud_wavstream.h>
#include <string>
#include <vector>

/**
 * @brief A system that handles audio playback and management.
 */
class AudioSystem : public System {
    friend class Engine;
    static SoLoud::Soloud _soLoud; // External engine for audio playback.
    static std::vector<std::pair<std::unique_ptr<SoLoud::WavStream>, unsigned int>> _audioClips; // List of audio clips and their handles.

    /**
     * @brief Checks if sounds are still playing.
     */
    static void Update();

    /**
     * @brief De-initializes SoLoud.
     */
    static void Clean();
public:
    /**
     * @brief Plays an audio clip.
     *
     * @param audioPath The path to the audio file.
     * @param loop Whether the audio should loop.
     * @param volume The volume of the audio.
     * @return The audio component associated with the played audio.
     */
    static AudioComponent PlayAudio(std::string audioPath, bool loop, float volume);

    /**
     * @brief Stops the playback of an audio clip.
     *
     * @param audio The audio component associated with the audio to stop.
     */
    static void StopAudio(AudioComponent& audio);

    /**
     * @brief Gets the playback position of an audio clip.
     *
     * @param audio The audio component associated with the audio.
     * @return The playback position of the audio.
     */
    static float GetAudioPosition(AudioComponent& audio);

    /**
     * @brief Sets the playback position of an audio clip.
     *
     * @param audio The audio component associated with the audio.
     * @param position The playback position to set.
     */
    static void SetAudioPosition(AudioComponent& audio, float position);

    /**
     * @brief Gets the volume of an audio clip.
     *
     * @param audio The audio component associated with the audio.
     * @return The volume of the audio.
     */
    static float GetAudioVolume(AudioComponent& audio);

    /**
     * @brief Sets the volume of an audio clip.
     *
     * @param audio The audio component associated with the audio.
     * @param volume The volume to set.
     */
    static void SetAudioVolume(AudioComponent& audio, float volume);

    /**
     * @brief Pauses the playback of an audio clip.
     *
     * @param audio The audio component associated with the audio to pause.
     */
    static void PauseAudio(AudioComponent& audio);

    /**
     * @brief Resumes the playback of a paused audio clip.
     *
     * @param audio The audio component associated with the audio to resume.
     */
    static void ResumeAudio(AudioComponent& audio);

    /**
     * @brief Stops the playback of all audio clips.
     */
    static void StopAllAudio();

    /**
     * @brief Sets the global volume for all audio playback.
     *
     * @param volume The global volume to set.
     */
    static void SetGlobalVolume(float volume);

/**
 * @brief Initializes SoLoud.
 */
static void Init();
};