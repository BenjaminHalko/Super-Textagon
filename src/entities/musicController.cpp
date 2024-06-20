#include "musicController.h"
#include "../global.h"
#include <engine/engine.h>
#include <engine/comp/depth.h>
#include <engine/comp/script.h>
#include <engine/sys/audioSystem.h>

// Updates the music controller
void UpdateMusicController(Entity& self) {
    // Define Variables
    static auto music = AudioSystem::PlayAudio("audio/music.ogg", true, 0.6f);
    static int lastBeat = 0;
    static const int BPM = 130;
    static bool paused = false;

    // Update Beats
    Global::musicTime = (AudioSystem::GetAudioPosition(music) * BPM / 60.0f);
    Global::beatPulse = ((int)Global::musicTime != lastBeat);
    lastBeat = (int)Global::musicTime;

    // Pause Music
    if (Global::gameOver) {
        if (!paused) {
            AudioSystem::PauseAudio(music);
            paused = true;
        }
    } else if (paused) {
        AudioSystem::ResumeAudio(music);
        paused = false;
    }
}

void CreateMusicController() {
    Engine::AddEntity(
        Depth(1000),
        Script(UpdateMusicController)
    );
}
