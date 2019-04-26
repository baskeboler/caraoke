#if !defined(SDL_UTILS_H)
#define SDL_UTILS_H

#include "globals.h"
#include "common.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

// Screen dimension constants
// extern const int SCREEN_WIDTH;
// extern const int SCREEN_HEIGHT;

// // The window we'll be rendering to
// extern SDL_Window *gWindow;
// extern SDL_Renderer *gRenderer;

// // The surface contained by the window
// extern SDL_Surface *gScreenSurface;
// extern SDL_Surface *gHelloWorld;
// extern TTF_Font *gFont;
// extern texture_t gTextTexture;

extern BOOL sdl_init() ;
extern BOOL loadMedia() ;
extern void cleanup();
#endif // SDL_UTILS_H

