#include "audio.h"


Mix_Music * audio_load_music(char* path) {
    return Mix_LoadMUS(path);
}

Mix_Chunk* audio_load_sample(char* path) {
    return Mix_LoadWAV(path);
}


status_t loadMusic() {
    gSong = audio_load_music("song.mp3");
    return STATUS_OK;
}