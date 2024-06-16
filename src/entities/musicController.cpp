#include "musicController.h"
#include <engine/engine.h>
#include <engine/comp/script.h>
#include <engine/sys/audioSystem.h>
#include "../global.h"

void UpdateMusicController(Entity& self) {
    // Define Variables
    static auto music = AudioSystem::PlayAudio("audio/music.ogg", true, 0.4f);
    static int lastBeat = 0;
    static const int BPM = 130;

    // Update Beats
    int beat = (int)(AudioSystem::GetAudioPosition(music) * BPM / 60);
    Global::beatPulse = (beat != lastBeat);
    lastBeat = beat;
}

void CreateMusicController() {
    Engine::AddEntity(
        "musicController", -10,
        Script(UpdateMusicController)
    );
}
