#if !defined(GLOBALS_H)
#define GLOBALS_H
#include "common.h"
#include "texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

// Screen dimension constants
static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;

// The window we'll be rendering to
static SDL_Window *gWindow = NULL;
static SDL_Renderer *gRenderer = NULL;

// The surface contained by the window
static SDL_Surface *gScreenSurface = NULL;
static SDL_Surface *gHelloWorld = NULL;
static TTF_Font *gFont = NULL;
static texture_t gTextTexture = NULL;

static Mix_Music* gSong = NULL;
#endif // GLOBALS_H
