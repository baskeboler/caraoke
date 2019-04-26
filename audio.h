#if !defined(AUDIO_H)
#define AUDIO_H
#include "common.h"
#include "globals.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

extern Mix_Music * audio_load_music(char* path);
extern Mix_Chunk* audio_load_sample(char* path);

extern status_t loadMusic() ;
#endif // AUDIO_H
