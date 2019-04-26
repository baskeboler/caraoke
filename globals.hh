#if !defined(GLOBALS_H)
#define GLOBALS_H
#include "common.hh"
#include "texture.hh"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <memory>

using std::shared_ptr;
// Screen dimension constants
static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;

// The window we'll be rendering to
static SDL_Window * gWindow = nullptr;
static SDL_Renderer * gRenderer = nullptr;

// The surface contained by the window
static SDL_Surface* gScreenSurface = nullptr;
static SDL_Surface* gHelloWorld = nullptr;
static TTF_Font* gFont = nullptr;
static shared_ptr<Texture> gTextTexture = nullptr;

static Mix_Music* gSong = nullptr;
#endif // GLOBALS_H
