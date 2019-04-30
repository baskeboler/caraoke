#if !defined(GLOBALS_H)
#define GLOBALS_H
#include "common.hh"
#include "texture.hh"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <memory>

using std::shared_ptr;

struct Globals {

  // Screen dimension constants
  static int SCREEN_WIDTH;
  static int SCREEN_HEIGHT;

  // The window we'll be rendering to
  static SDL_Window *gWindow;
  static SDL_Renderer *gRenderer;

  // The surface contained by the window
  static SDL_Surface *gScreenSurface;
  static SDL_Surface *gHelloWorld;
  static TTF_Font *gFont;
  static shared_ptr<Texture> gTextTexture;

  static Mix_Music *gSong;
};

#endif // GLOBALS_H
