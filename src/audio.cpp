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

bool loadMusic() {
    auto app = App::get_instance();
    Mix_Music* music = audio_load_music("song.mp3");
    if (music != nullptr) {
        app->set_song( music);
    } else {
        return false;
    }
    return true;
}