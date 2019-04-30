#include "audio.hh"
#include <memory>
#include "app.hh"
using std::shared_ptr;

Mix_Music* audio_load_music(const char* path) {
    return Mix_LoadMUS(path);
}

Mix_Chunk* audio_load_sample(const char* path) {
    return Mix_LoadWAV(path);
}
