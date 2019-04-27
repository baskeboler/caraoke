#if !defined(AUDIO_H)
#define AUDIO_H
#include "common.hh"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <memory>
using std::shared_ptr;

extern Mix_Music * audio_load_music(char* path);
extern Mix_Chunk * audio_load_sample(char* path);

extern bool loadMusic() ;
#endif // AUDIO_H
