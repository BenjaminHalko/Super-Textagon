#include "musicController.h"
#include "../global.h"
#include <engine/engine.h>
#include <engine/comp/depth.h>
#include <engine/comp/script.h>
#include <engine/sys/audioSystem.h>

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
        Depth(1000),
        Script(UpdateMusicController)
    );
}
