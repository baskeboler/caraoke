#include "audio.hh"
#include <memory>
using std::shared_ptr;

Mix_Music* audio_load_music(const char* path) {
    return Mix_LoadMUS(path);
}

Mix_Chunk* audio_load_sample(const char* path) {
    return Mix_LoadWAV(path);
}

extern Mix_Music* gSong;
bool loadMusic() {
    Globals::gSong = audio_load_music("song.mp3");
    return true;
}